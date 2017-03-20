
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

LIST(APPEND OpcUaSensorInterface_SRC
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-sensor-interface/DeviceData.cpp
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-sensor-interface/DeviceData.h
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-sensor-interface/DeviceDataFile.cpp
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-sensor-interface/DeviceDataFile.h
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-sensor-interface/Device.h
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-sensor-interface/DeviceDataValue.h
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-sensor-interface/DeviceDataLWM2M.cpp
  ${PROJECT_SOURCE_DIR}/../../niki/opcua-sensor-interface/DeviceDataLWM2M.h
)

add_library(OpcUaSensorInterface SHARED ${OpcUaSensorInterface_SRC})

target_link_libraries(
    OpcUaSensorInterface
    ${CMAKE_DL_LIBS}
    ${Boost_LIBRARIES}
)


# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# install
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
file(GLOB INC_OpcUaSensorInterface ${PROJECT_SOURCE_DIR}/OpcUaSensorInterface/*.h)


install(TARGETS OpcUaSensorInterface DESTINATION ${LIB_DIR}/OpcUaStack)
install(FILES ${INC_OpcUaSensorInterface} DESTINATION ${INC_DIR}/OpcUaStack/OpcUaSensorInterface)



