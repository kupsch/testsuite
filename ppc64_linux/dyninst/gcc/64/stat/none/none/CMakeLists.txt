# CMakeLists for dyninst/gcc/64/stat/none/none
set (CMAKE_C_FLAGS "${MUTATOR_DEFINES}  ${CFLAGS} ${MUTATEE_CFLAGS_GNU}  -m64 -g -O0 -no-pie")
set (CMAKE_C_FLAGS_DEBUG "")
set (CMAKE_C_FLAGS_RELEASE "")
set (CMAKE_C_FLAGS_RELWITHDEBINFO "")
set (CMAKE_C_COMPILER "${M_gnu_cc}")
include_directories("${PROJECT_SOURCE_DIR}/testsuite/src")
include_directories("${PROJECT_SOURCE_DIR}/testsuite/src/dyninst")
add_definitions(-DSOLO_MUTATEE)
set (CMAKE_SKIP_INSTALL_RPATH TRUE)
set (CMAKE_EXE_LINKER_FLAGS "${MUTATEE_LDFLAGS_GNU} -m64 -static")
IF (NOT ${M_gnu_cc} MATCHES "NOTFOUND")
CHECK_MUTATEE_COMPILER ("${M_gnu_cc}"
	"${MUTATOR_DEFINES}  ${CFLAGS} ${MUTATEE_CFLAGS_GNU}  -m64 -g -O0 -no-pie"
	"${MUTATEE_LDFLAGS_GNU} -m64 -static"
	"C"
	"gnu_cc 64 stat"
	MUTATEEgnucc64statC)

IF (MUTATEEgnucc64statC MATCHES "1")
include (${PROJECT_SOURCE_DIR}/ppc64_linux/srclists.cmake)
if(TARGET dyninstAPI)
add_executable (dyninst_group_test.stat_gcc_64_none_none ${SOURCE_LIST_51})
foreach (f ${SOURCE_LIST_51})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(dyninst_group_test.stat_gcc_64_none_none PROPERTIES LINKER_LANGUAGE C)
target_link_libraries (dyninst_group_test.stat_gcc_64_none_none ${CMAKE_DL_LIBS})
add_executable (test1_14.stat_gcc_64_none_none ${SOURCE_LIST_44})
foreach (f ${SOURCE_LIST_44})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(test1_14.stat_gcc_64_none_none PROPERTIES LINKER_LANGUAGE C)
add_executable (test1_29.stat_gcc_64_none_none ${SOURCE_LIST_4})
foreach (f ${SOURCE_LIST_4})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE C)
	endif()
	endforeach()
set_target_properties(test1_29.stat_gcc_64_none_none PROPERTIES LINKER_LANGUAGE C)


INSTALL (TARGETS
		dyninst_group_test.stat_gcc_64_none_none
		test1_14.stat_gcc_64_none_none
		test1_29.stat_gcc_64_none_none
	DESTINATION ${INSTALL_DIR})

ENDIF()
ENDIF()
ENDIF()
