#Description: XIP Board Driver; user_visible: True
include_guard(GLOBAL)
message("driver_xip_board_evkbmimxrt1170 component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/evkbmimxrt1170_flexspi_nor_config.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_common)
