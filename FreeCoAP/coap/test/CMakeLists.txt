set(EXECUTABLE_OUTPUT_PATH ${OUTDIR}/coap/test)

include_directories(
	${TOPDIR}/coap/include
)

link_directories(
)


#################################
add_executable(test_coap_client test.c test_coap_client.c)
target_link_libraries(test_coap_client coap gmp hogweed nettle gnutls)


#################################
add_executable(test_coap_server test.c test_coap_server.c)
target_link_libraries(test_coap_server coap gmp hogweed nettle gnutls)


#################################
add_executable(test_coap_msg test.c test_coap_msg.c)
target_link_libraries(test_coap_msg coap)


#################################
add_executable(test_config test.c test_config.c)
target_link_libraries(test_config coap)


#################################
add_executable(test_cross test.c test_cross.c)
target_link_libraries(test_cross coap)


#################################
add_executable(test_uri test.c test_uri.c)
target_link_libraries(test_uri coap)


#################################
add_executable(test_lock test.c test_lock.c)
target_link_libraries(test_lock coap pthread)


#################################
add_executable(test_thread test.c test_thread.c)
target_link_libraries(test_thread coap pthread)


#################################
add_executable(test_data_buf test.c test_data_buf.c)
target_link_libraries(test_data_buf coap)


#################################
add_executable(test_http_msg test.c test_http_msg.c)
target_link_libraries(test_http_msg coap)


#################################
add_executable(test_http_client test.c test_http_client.c)
target_link_libraries(test_http_client coap gmp hogweed nettle gnutls pthread)