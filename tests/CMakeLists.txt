set(sources
	00_base
	01_sans_atomic
	02_lock_free_queue
)

foreach(test IN LISTS sources)
	add_executable("${test}" "${test}.cpp")
	target_link_libraries("${test}" "-lpthread")
	set_target_properties("${test}" PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
endforeach()
