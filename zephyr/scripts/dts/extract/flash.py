#
# Copyright (c) 2018 Bobby Noelte
#
# SPDX-License-Identifier: Apache-2.0
#

from extract.globals import *
from extract.directive import DTDirective

from extract.default import default

##
# @brief Manage flash directives.
#
class DTFlash(DTDirective):
    def __init__(self):
        self._flash_area = {}

    def _extract_partition(self, node_path):
        prop_def = {}
        prop_alias = {}
        node = reduced[node_path]

        # Build Index based partition IDs
        if node_path not in self._flash_area:
            self._flash_area[node_path] = len(self._flash_area)
        area_id = self._flash_area[node_path]

        # Extract a per partition dev name, something like:
        # #define DT_FLASH_AREA_1_DEV             "FLASH_CTRL"

        # For now assume node_path is something like:
        # /flash-controller@4001E000/flash@0/partitions/partition@fc000
        # first we go up 2 levels to get the flash, check its compat
        #
        # The flash controller might be the flash itself (for cases like NOR
        # flashes), for the case of 'soc-nv-flash' we assume its the parent
        # of the flash node.
        controller_path = '/' + '/'.join(node_path.split('/')[1:-2])
        if get_compat(controller_path) == "soc-nv-flash":
            controller_path = '/' + '/'.join(node_path.split('/')[1:-3])

        for flash_path in self._flash_area:
            if controller_path in flash_path:
                prop_def["DT_FLASH_AREA_{}_DEV".format(area_id)] = \
                    '"' + reduced[controller_path]['props']['label'] + '"'

        partition_label = str_to_label(node['props']['label'])
        prop_def["DT_FLASH_AREA_{}_LABEL".format(area_id)] = partition_label
        prop_def["DT_FLASH_AREA_{}_ID".format(partition_label)] = area_id

        reg = node['props']['reg']
        for i in range(len(reg)//2):
            prop_def["DT_FLASH_AREA_{}_OFFSET_{}".format(area_id, i)] = reg[2*i]
            prop_def["DT_FLASH_AREA_{}_SIZE_{}".format(area_id, i)] = reg[2*i + 1]

        prop_def["DT_FLASH_AREA_NUM"] = len(self._flash_area)

        # Alias sector 0
        prop_alias[
            "DT_FLASH_AREA_{}_OFFSET".format(area_id)
        ] = "DT_FLASH_AREA_{}_OFFSET_0".format(area_id)
        prop_alias[
            "DT_FLASH_AREA_{}_SIZE".format(area_id)
        ] = "DT_FLASH_AREA_{}_SIZE_0".format(area_id)

        insert_defs("DT_FLASH_AREA", prop_def, prop_alias)

    def _create_legacy_label(self, prop_alias, label):
        prop_alias[label.lstrip('DT_')] = label

    def extract_partition(self, node_path):
        prop_def = {}
        prop_alias = {}
        node = reduced[node_path]

        self._extract_partition(node_path)

        partition_label = str_to_label(node['props']['label'])

        label = "DT_FLASH_AREA_{}_LABEL".format(partition_label)
        prop_def[label] = '"' + node['props']['label'] + '"'
        self._create_legacy_label(prop_alias, label)

        label = "DT_FLASH_AREA_{}_READ_ONLY".format(partition_label)
        prop_def[label] = 1 if 'read-only' in node['props'] else 0
        self._create_legacy_label(prop_alias, label)

        reg = node['props']['reg']
        for i in range(len(reg)//2):
            label = "DT_FLASH_AREA_{}_OFFSET_{}".format(partition_label, i)
            prop_def[label] = reg[2*i]
            self._create_legacy_label(prop_alias, label)

            label = "DT_FLASH_AREA_{}_SIZE_{}".format(partition_label, i)
            prop_def[label] = reg[2*i + 1]
            self._create_legacy_label(prop_alias, label)

        # Alias sector 0

        label = "DT_FLASH_AREA_{}_OFFSET".format(partition_label)
        prop_alias[label] = "DT_FLASH_AREA_{}_OFFSET_0".format(partition_label)
        self._create_legacy_label(prop_alias, label)

        label = "DT_FLASH_AREA_{}_SIZE".format(partition_label)
        prop_alias[label] = "DT_FLASH_AREA_{}_SIZE_0".format(partition_label)
        self._create_legacy_label(prop_alias, label)

        insert_defs(node_path, prop_def, prop_alias)

    def extract_flash(self):
        node_path = chosen.get('zephyr,flash')
        if not node_path:
            # Add addr/size 0 for systems with no flash controller. This is
            # what they already do in the Kconfig options anyway.
            insert_defs('dummy-flash',
                        {'DT_FLASH_BASE_ADDRESS': 0, 'DT_FLASH_SIZE': 0},
                        {})
            return

        flash_node = reduced[node_path]
        orig_node_addr = node_path

        nr_address_cells, nr_size_cells = get_addr_size_cells(node_path)
        # if the nr_size_cells is 0, assume a SPI flash, need to look at parent
        # for addr/size info, and the second reg property (assume first is mmio
        # register for the controller itself)
        is_spi_flash = False
        if nr_size_cells == 0:
            is_spi_flash = True
            node_path = get_parent_path(node_path)
            (nr_address_cells, nr_size_cells) = get_addr_size_cells(node_path)

        reg = reduced[node_path]['props']['reg']
        if type(reg) is not list: reg = [ reg, ]
        props = list(reg)

        num_reg_elem = len(props)/(nr_address_cells + nr_size_cells)

        # if we found a spi flash, but don't have mmio direct access support
        # which we determin by the spi controller node only have on reg element
        # (ie for the controller itself and no region for the MMIO flash access)
        if num_reg_elem == 1 and is_spi_flash:
            node_path = orig_node_addr
        else:
            # We assume the last reg property is the one we want
            while props:
                addr = 0
                size = 0

                for x in range(nr_address_cells):
                    addr += props.pop(0) << (32 * (nr_address_cells - x - 1))
                for x in range(nr_size_cells):
                    size += props.pop(0) << (32 * (nr_size_cells - x - 1))

            addr += translate_addr(addr, node_path, nr_address_cells,
                                   nr_size_cells)

            insert_defs(node_path,
                        {'DT_FLASH_BASE_ADDRESS': hex(addr),
                         'DT_FLASH_SIZE': size//1024},
                        {})

        for prop in 'write-block-size', 'erase-block-size':
            if prop in flash_node['props']:
                default.extract(node_path, prop, None, 'DT_FLASH')

                # Add an non-DT prefix alias for compatiability
                prop_alias = {}
                label_post = '_' + str_to_label(prop)
                prop_alias['FLASH' + label_post] = 'DT_FLASH' + label_post
                insert_defs(node_path, {}, prop_alias)


    def extract_code_partition(self):
        node_path = chosen.get('zephyr,code-partition')
        if not node_path:
            # Fall back on zephyr,flash if zephyr,code-partition isn't set.
            # node_path will be 'dummy-flash' if neither is set.
            node_path = chosen.get('zephyr,flash', 'dummy-flash')

        node = reduced.get(node_path)

        if node and node is not reduced.get(chosen.get('zephyr,flash')):
            # only compute the load offset if the code partition
            # is not the same as the flash base address
            load_offset = node['props']['reg'][0]
            load_size = node['props']['reg'][1]
        else:
            load_offset = 0
            load_size = 0

        insert_defs(node_path,
                    {'DT_CODE_PARTITION_OFFSET': load_offset,
                     'DT_CODE_PARTITION_SIZE': load_size},
                    {})


##
# @brief Management information for flash.
flash = DTFlash()
