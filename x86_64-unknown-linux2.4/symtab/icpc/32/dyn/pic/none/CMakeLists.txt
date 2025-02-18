# CMakeLists for symtab/icpc/32/dyn/pic/none
set (CMAKE_CXX_FLAGS "${MUTATOR_DEFINES}  ${CXXFLAGS}  ${MUTATEE_CXXFLAGS_GNU}   -Di386_unknown_linux2_4 -Dm32_test -g -O0 -fPIC -fPIE -pie")
set (CMAKE_CXX_FLAGS_DEBUG "")
set (CMAKE_CXX_FLAGS_RELEASE "")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "")
set (CMAKE_CXX_COMPILER "${M_intel_CC_32}")
include_directories("${PROJECT_SOURCE_DIR}/testsuite/src")
include_directories("${PROJECT_SOURCE_DIR}/testsuite/src/symtab")
add_definitions(-DSOLO_MUTATEE)
set (CMAKE_EXE_LINKER_FLAGS "${MUTATEE_LDFLAGS_GNU} -Di386_unknown_linux2_4 -Dm32_test -Xlinker -export-dynamic")
IF (NOT ${M_intel_CC_32} MATCHES "NOTFOUND")
CHECK_MUTATEE_COMPILER ("${M_intel_CC_32}"
	"${MUTATOR_DEFINES}  ${CXXFLAGS}  ${MUTATEE_CXXFLAGS_GNU}   -Di386_unknown_linux2_4 -Dm32_test -g -O0 -fPIC -fPIE -pie"
	"${MUTATEE_LDFLAGS_GNU} -Di386_unknown_linux2_4 -Dm32_test -Xlinker -export-dynamic"
	"CXX"
	"intel_CC_32 32 dyn"
	MUTATEEintelCC3232dynCXX)

IF (MUTATEEintelCC3232dynCXX MATCHES "1")
include (${PROJECT_SOURCE_DIR}/x86_64-unknown-linux2.4/srclists.cmake)
if(TARGET symtabAPI)
add_executable (symtab_group_test.dyn_icpc_32_pic_none ${SOURCE_LIST_66})
foreach (f ${SOURCE_LIST_66})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE CXX)
	endif()
	endforeach()
set_target_properties(symtab_group_test.dyn_icpc_32_pic_none PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries (symtab_group_test.dyn_icpc_32_pic_none testA_m32)
add_executable (test_exception.dyn_icpc_32_pic_none ${SOURCE_LIST_63})
foreach (f ${SOURCE_LIST_63})
	get_source_file_property(lang ${f} LANGUAGE)
	if(lang MATCHES "C")
		set_source_files_properties(${f} PROPERTIES LANGUAGE CXX)
	endif()
	endforeach()
set_target_properties(test_exception.dyn_icpc_32_pic_none PROPERTIES LINKER_LANGUAGE CXX)


INSTALL (TARGETS
		symtab_group_test.dyn_icpc_32_pic_none
		test_exception.dyn_icpc_32_pic_none
	DESTINATION ${INSTALL_DIR})

ENDIF()
ENDIF()
ENDIF()
