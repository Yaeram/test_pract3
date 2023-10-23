project(crypto_utils_lib)

set(HEADER_FILES
        crypto_utils.h
        utils.h
        )
set(SOURCE_FILES
        utils.cpp
        crypto_utils.cpp
        )
add_library(crypto_utils_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})