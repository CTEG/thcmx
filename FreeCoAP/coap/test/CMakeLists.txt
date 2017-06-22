set(EXECUTABLE_OUTPUT_PATH ${OUTDIR}/coap/test)

include_directories(
	${TOPDIR}/coap/include
)

link_directories(
)

#################################
add_executable(test_coap_client test.c test_coap_client.c)
target_link_libraries(test_coap_client coap gmp hogweed nettle gnutls)
