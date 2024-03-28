function(set_package_root PACKAGE ROOTDIR)
    string(TOUPPER ${PACKAGE} PACKAGE_UPPER)
    if(${CONAN_${PACKAGE_UPPER}_ROOT})
        set(${ROOTDIR} ${CONAN_${PACKAGE_UPPER}_ROOT} PARENT_SCOPE)
    else()
        if(${CONAN_${PACKAGE_UPPER}_ROOT_RELEASE})
            set(${ROOTDIR} ${CONAN_${PACKAGE_UPPER}_ROOT_RELEASE} PARENT_SCOPE)
        else()
            set(${ROOTDIR} ${CONAN_${PACKAGE_UPPER}_ROOT_DEBUG} PARENT_SCOPE)
        endif()
    endif()
endfunction()

function(set_package_root_postfix PACKAGE ROOTDIR POSTFIX)
    string(TOUPPER ${PACKAGE} PACKAGE_UPPER)
    if(${CONAN_${PACKAGE_UPPER}_ROOT})
        set(${ROOTDIR} ${CONAN_${PACKAGE_UPPER}_ROOT}${POSTFIX} PARENT_SCOPE)
    else()
        if(${CONAN_${PACKAGE_UPPER}_ROOT_RELEASE})
            set(${ROOTDIR} ${CONAN_${PACKAGE_UPPER}_ROOT_RELEASE}${POSTFIX} PARENT_SCOPE)
        else()
            set(${ROOTDIR} ${CONAN_${PACKAGE_UPPER}_ROOT_DEBUG}${POSTFIX} PARENT_SCOPE)
        endif()
    endif()
endfunction()