cmake_minimum_required(VERSION 3.16.0)

include( $ENV{IDF_PATH}/tools/cmake/version.cmake )

idf_component_register(
    SRCS "cla.c" "matrix.c" "vector.c"
    INCLUDE_DIRS "include" "assets/data"
)
