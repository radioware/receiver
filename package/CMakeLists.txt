set(CPACK_PACKAGE_NAME "${APPLICATION_NAME}")
set(CPACK_PACKAGE_VENDOR "${ORGANIZATION_NAME}")

set(CPACK_PACKAGE_VERSION_MAJOR "${APPLICATION_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${APPLICATION_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${APPLICATION_VERSION_PATCH}")

set(CPACK_PACKAGE_VERSION "${APPLICATION_VERSION}")
set(CPACK_PACKAGE_CONTACT "sadylan@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Simple Radio Receiver with RTL-SDR devices for RadioWare project")
set(CPACK_PACKAGE_EXECUTABLES radioware_receiver "RadioWare Receiver")

set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.md")
set(CPACK_RESOURCE_FILE_README "${PROJECT_SOURCE_DIR}/README.md")

set(CPACK_GENERATOR "DEB")

execute_process(COMMAND dpkg --print-architecture
        OUTPUT_VARIABLE CPACK_DEBIAN_PACKAGE_ARCHITECTURE
        OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CPACK_DEBIAN_PACKAGE_SECTION "misc")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)
set(CPACK_DEBIAN_PACKAGE_CONTROL_STRICT_PERMISSION TRUE)

set(CPACK_PACKAGE_FILE_NAME "radioware_receiver-${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")

set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")

set(RADIOWARE_RECEIVER_SYSTEM_USER radioware)
set(RADIOWARE_RECEIVER_SYSTEM_GROUP radioware)
set(RADIOWARE_RECEIVER_SYSTEM_BINDIR "${CPACK_PACKAGING_INSTALL_PREFIX}/${CMAKE_INSTALL_BINDIR}")
set(RADIOWARE_RECEIVER_SYSTEM_HOMEDIR "/${CMAKE_INSTALL_LOCALSTATEDIR}/lib/radioware")
set(RADIOWARE_RECEIVER_SYSTEM_CONFDIR "/${CMAKE_INSTALL_SYSCONFDIR}/radioware")
set(RADIOWARE_RECEIVER_SYSTEM_PIDDIR "/${CMAKE_INSTALL_RUNSTATEDIR}/radioware")
set(RADIOWARE_RECEIVER_SYSTEM_LOGDIR "/${CMAKE_INSTALL_LOCALSTATEDIR}/log/radioware")

install(FILES ${PROJECT_SOURCE_DIR}/LICENSE.md
        DESTINATION "${CMAKE_INSTALL_DOCDIR}"
        COMPONENT radioware_receiver)

install(FILES ${PROJECT_SOURCE_DIR}/README.md
        DESTINATION "${CMAKE_INSTALL_DOCDIR}"
        COMPONENT radioware_receiver)

configure_file(receiver.conf.in receiver.conf @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/package/receiver.conf
        DESTINATION "${RADIOWARE_RECEIVER_SYSTEM_CONFDIR}"
        RENAME "receiver.conf-vanilla"
        PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
        COMPONENT radioware_receiver)

configure_file(radioware-receiver.service.in radioware-receiver.service @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/package/radioware-receiver.service
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/systemd/system"
        COMPONENT radioware_receiver)

configure_file(radioware-receiver.logrotate.in radioware-receiver.logrotate @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/package/radioware-receiver.logrotate
        DESTINATION "/etc/logrotate.d"
        RENAME "radioware-receiver"
        COMPONENT radioware_receiver)

configure_file(preinst.in preinst @ONLY)
configure_file(postinst.in postinst @ONLY)
configure_file(prerm.in prerm @ONLY)
configure_file(postrm.in postrm @ONLY)
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_BINARY_DIR}/package/preinst;${CMAKE_BINARY_DIR}/package/postinst;${CMAKE_BINARY_DIR}/package/prerm;${CMAKE_BINARY_DIR}/package/postrm")

include(CPack)

cpack_add_component(radioware_receiver
        DISPLAY_NAME "RadioWare Receiver"
        DESCRIPTION "Simple Radio Receiver with RTL-SDR devices for RadioWare project"
        REQUIRED)
