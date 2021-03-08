
macro(copy_content TARNAME DESTDIR)
    
    foreach(it ${ARGN})
        
        get_filename_component(INFILE ${it} ABSOLUTE)
        get_filename_component(OUTFILE ${it} NAME)
        get_filename_component(DIR ${DESTDIR} ABSOLUTE )

        add_custom_command(TARGET ${TARNAME} 
                            POST_BUILD
                            COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${INFILE} 
                            "${DIR}/Content/${OUTFILE}"
                            )
    endforeach()

endmacro()


macro(copy_target TARNAME DESTDIR)

    add_custom_command(TARGET ${TARNAME} 
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${TARNAME}> 
                       "${DESTDIR}/$<TARGET_FILE_NAME:${TARNAME}>"
                       )

    if (MSVC)
        set_target_properties(
            ${TARNAME} 
            PROPERTIES 
            VS_DEBUGGER_COMMAND  
           "${DESTDIR}/$<TARGET_FILE_NAME:${TARNAME}>"
        )
    endif()

endmacro(copy_target)



macro(copy_install_target TARNAME)

    if (NOT ${ToyVM_INSTALL_PATH} STREQUAL "")
        if (NOT ${ARGN} STREQUAL "")
            install(TARGETS ${TARNAME}
                    DESTINATION "${ToyVM_INSTALL_PATH}/${ARGN}/"
	        )
        else()
            install(TARGETS ${TARNAME}
                    DESTINATION "${ToyVM_INSTALL_PATH}"
	        )
        endif()
    endif()


endmacro(copy_install_target)
