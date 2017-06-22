include_directories(
	${TOPDIR}/coap/include
)

file(GLOB_RECURSE HEADERFILES "../include/*")
aux_source_directory(. DIR_SRCS)
add_library(coap ${DIR_SRCS} ${HEADERFILES})

