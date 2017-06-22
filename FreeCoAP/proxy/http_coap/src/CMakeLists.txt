set(EXECUTABLE_OUTPUT_PATH ${OUTDIR}/proxy/http_coap/)

include_directories(
	${TOPDIR}/coap/include
	${TOPDIR}/proxy/http_coap/include
)

link_directories(
)


#################################
add_executable(http_coap connection.c listener.c param.c proxy.c)
target_link_libraries(http_coap coap gmp hogweed nettle gnutls pthread)