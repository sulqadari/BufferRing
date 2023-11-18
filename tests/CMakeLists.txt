set(sources
	00_base
	01_sans_atomic
)

foreach(test IN LISTS sources)
	add_executable("${test}" "${test}.cpp")
	set_target_properties("${test}" PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")
endforeach()
