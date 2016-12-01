
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------
#
# build 
# 
# -----------------------------------------------------------------------------
# -----------------------------------------------------------------------------

include_directories(
   ${PROJECT_SOURCE_DIR}/OpcUaSensorInterface
)

file(GLOB OpcUaSensorInterface_SRC ${PROJECT_SOURCE_DIR}/OpcUaSensorInterface/*.cpp)
MESSAGE( STATUS "sourcefiles: " ${OpcUaSensorInterface_SRC} )
MESSAGE( STATUS "proje source: " ${PROJECT_SOURCE_DIR} )

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



