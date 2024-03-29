cmake_minimum_required(VERSION 3.21...3.27)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# NOTE: We need LANGUAGE C too for libdes. It may be required to build at Windows! CK
project(
  snmp_pp
  VERSION 3.4.7.14
  LANGUAGES CXX C
)

include(CheckIncludeFiles)
include(CheckFunctionExists)
include(CheckSymbolExists)
include(CheckLibraryExists)
include(CheckStructHasMember)
include(CheckTypeSize)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# =======================================
set(CMAKE_CXX_STANDARD 17)
# =======================================
# NOTE: in consideration of std=c++17! CK
set(CNF_STDCXX_98_HEADERS YES)
set(HAVE_INTTYPES_H YES)
set(SNMP_PP_NAMESPACE ON) # "Enable using of namespace (needed!)" ON)
set(SNMP_PP_SNMPv3 ON) # "Enable support for SNMPv3 (needed!)" ON)
set(SNMP_PP_THREADS ON) # "Enable support for threads (needed!)" ON)

if(NOT PROJECT_IS_TOP_LEVEL)
  option(CMAKE_SKIP_INSTALL_RULES "Whether to disable generation of installation rules" YES)
endif()

option(SNMP_PP_EXAMPLES "Enable to build examples" ON)
option(SNMP_PP_EXTENDED_DEBUG "Enable additional debug messages" OFF)
option(SNMP_PP_IPXADDR "Enable IpxAddress class" OFF)
option(SNMP_PP_IPv6 "Enable support for IPv6" ON)
option(SNMP_PP_LIBDES "Search for DES library (At least needed for Windows!)" ON)
option(SNMP_PP_LIBTOMCRYPT "Search for Tomcrypt library" OFF)
option(SNMP_PP_LOGGING "Enable logging" ${PROJECT_IS_TOP_LEVEL})
option(SNMP_PP_MACADDR "Enable MacAddress class" OFF)
option(SNMP_PP_OPENSSL "Search for OpenSSL library" ON)

if(SNMP_PP_LOGGING)
  set(LogProfile
      "original"
      CACHE STRING "Log Profile"
  )

  set(LogProfileValues
      "original;off;quiet;std;events;verbose;full;debug;schwafel"
      CACHE STRING "List of possible values for the Log Profile variable"
  )

  set_property(CACHE LogProfile PROPERTY STRINGS ${LogProfileValues})

  message(STATUS "LogProfile='${LogProfile}'")
endif()

set(VERSION ${PROJECT_VERSION})
set(SNMP_PP_MAJOR_VERSION ${PROJECT_VERSION_MAJOR})
set(SNMP_PP_MINOR_VERSION ${PROJECT_VERSION_MINOR})
set(SNMP_PP_MICRO_VERSION ${PROJECT_VERSION_PATCH})

message(STATUS "snmp++ Version ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

check_include_files(sys/param.h CNF_HAVE_SYS_PARAM_H)
check_include_files(sys/stat.h CNF_HAVE_SYS_STAT_H)
check_include_files(sys/time.h CNF_HAVE_SYS_TIME_H)
check_include_files(sys/timeb.h CNF_HAVE_SYS_TIMEB_H)
check_include_files(sys/types.h CNF_HAVE_SYS_TYPES_H)

if(MSVC)
  check_include_files(io.h CNF_HAVE_IO_H)
  check_include_files(process.h CNF_HAVE_PROCESS_H)
  check_include_files(winsock2.h CNF_HAVE_WINSOCK2_H)
  check_include_files(ws2tcpip.h CNF_HAVE_WS2TCPIP_H)
  check_include_files(wspiapi.h CNF_HAVE_WSPIAPI_H)
  check_function_exists("_getpid" CNF_HAVE__GETPID)
else()
  check_include_files(sys/unistd.h CNF_HAVE_SYS_UNISTD_H)
  check_include_files(unistd.h CNF_HAVE_UNISTD_H)
endif()

check_include_files(arpa/inet.h CNF_HAVE_ARPA_INET_H)
check_include_files(netdb.h CNF_HAVE_NETDB_H)
check_include_files(netinet/in.h CNF_HAVE_NETINET_IN_H)
check_include_files(poll.h CNF_HAVE_POLL_H)
check_include_files(pthread.h CNF_HAVE_PTHREAD_H)
check_include_files(sys/select.h CNF_HAVE_SYS_SELECT_H)
check_include_files(sys/socket.h CNF_HAVE_SYS_SOCKET_H)
set(HAVE_PTHREAD ${CNF_HAVE_PTHREAD_H})

check_function_exists("strcasecmp" CNF_HAVE_STRCASECMP)
check_function_exists("stricmp" CNF_HAVE_STRICMP)
check_function_exists("getpid" CNF_HAVE_GETPID)
set(HAVE_GETPID ${CNF_HAVE_GETPID})
set(HAVE_STRCASECMP ${CNF_HAVE_STRCASECMP})

if(NOT MSVC)
  check_function_exists("clock_gettime" HAVE_CLOCK_GETTIME)
  check_function_exists("getaddrinfo" HAVE_GETADDRINFO)
  check_function_exists("gethostbyaddr" HAVE_GETHOSTBYADDR)
  check_function_exists("gethostbyaddr_r" HAVE_GETHOSTBYADDR_R)
  check_function_exists("gethostbyname" HAVE_GETHOSTBYNAME)
  check_function_exists("gethostbyname2" HAVE_GETHOSTBYNAME2)
  check_function_exists("gethostbyname_r" HAVE_GETHOSTBYNAME_R)
  check_function_exists("gethostname" HAVE_GETHOSTNAME)
  check_function_exists("gettimeofday" HAVE_GETTIMEOFDAY)
  check_function_exists("htonl" HAVE_HTONL)
  check_function_exists("inet_aton" HAVE_INET_ATON)
  check_function_exists("inet_ntoa" HAVE_INET_NTOA)
  check_function_exists("inet_ntop" HAVE_INET_NTOP)
  check_function_exists("inet_pton" HAVE_INET_PTON)
  check_function_exists("isdigit" HAVE_ISDIGIT)
  check_function_exists("localtime_r" HAVE_LOCALTIME_R)
  check_function_exists("malloc" HAVE_MALLOC)
  check_function_exists("memset" HAVE_MEMSET)
  check_function_exists("poll" HAVE_POLL)
  check_function_exists("realloc" HAVE_REALLOC)
  check_function_exists("select" HAVE_SELECT)
  check_function_exists("socket" HAVE_SOCKET)
  check_function_exists("strchr" HAVE_STRCHR)
  check_function_exists("strerror" HAVE_STRERROR)
  check_function_exists("strstr" HAVE_STRSTR)
else()
  set(HAVE_GETADDRINFO YES)
  set(HAVE_HTONL YES)
  set(HAVE_INET_NTOP YES)
  set(HAVE_INET_PTON YES)
  set(HAVE_MALLOC YES)
  set(HAVE_MEMSET YES)
  set(HAVE_REALLOC YES)
  set(HAVE_SELECT YES)
  set(HAVE_STRCHR YES)
  set(HAVE_STRERROR YES)
  set(HAVE_STRSTR YES)
endif()

check_type_size("int64_t" SIZEOF_INT64_T LANGUAGE CXX)
check_type_size("long long" SIZEOF_LONG_LONG LANGUAGE CXX)
check_type_size("long" SIZEOF_LONG LANGUAGE CXX)
check_type_size("uint64_t" SIZEOF_UINT64_T LANGUAGE CXX)
check_type_size("unsigned long long" SIZEOF_ULONG_LONG LANGUAGE CXX)
check_type_size("unsigned long" SIZEOF_ULONG LANGUAGE CXX)

if(SIZEOF_INT64_T EQUAL "8")
  set(TYPE_INT64_T "int64_t")
elseif(SIZEOF_LONG EQUAL "8")
  set(TYPE_INT64_T "long")
elseif(SIZEOF_LONG_LONG EQUAL "8")
  set(TYPE_INT64_T "long long")
else()
  message(FATAL_ERROR "Can't find suitable int64_t")
endif()
message(STATUS "Found int64_t: ${TYPE_INT64_T}")

if(SIZEOF_UINT64_T EQUAL "8")
  set(TYPE_UINT64_T "uint64_t")
elseif(SIZEOF_ULONG EQUAL "8")
  set(TYPE_INT64_T "unsigned long")
elseif(SIZEOF_ULONG_LONG EQUAL "8")
  set(TYPE_INT64_T "unsigned long long")
else()
  message(FATAL_ERROR "Can't find suitable uint64_t")
endif()
message(STATUS "Found uint64_t: ${TYPE_UINT64_T}")

set(SOCKADDR_HEADERS)
if(CNF_HAVE_WINSOCK2_H)
  set(SOCKADDR_HEADERS ${SOCKADDR_HEADERS} winsock2.h)
endif()
if(CNF_HAVE_WS2TCPIP_H)
  set(SOCKADDR_HEADERS ${SOCKADDR_HEADERS} ws2tcpip.h)
endif()
if(CNF_HAVE_NETDB_H)
  set(SOCKADDR_HEADERS ${SOCKADDR_HEADERS} netdb.h)
endif()
if(CNF_HAVE_SYS_SOCKET_H)
  set(SOCKADDR_HEADERS ${SOCKADDR_HEADERS} sys/socket.h)
endif()
if(CNF_HAVE_ARPA_INET_H)
  set(SOCKADDR_HEADERS ${SOCKADDR_HEADERS} arpa/inet.h)
endif()
if(CNF_HAVE_NETINET_IN_H)
  set(SOCKADDR_HEADERS ${SOCKADDR_HEADERS} netinet/in.h)
endif()

check_struct_has_member(
  "struct sockaddr_storage" ss_family "${SOCKADDR_HEADERS}" CNF_HAVE_STRUCT_SOCKADDR_STORAGE_SS_FAMILY LANGUAGE CXX
)

if(SNMP_PP_SNMPv3)
  set(_SNMPv3 1)
  set(_NO_SNMPv3 0)
else()
  set(_SNMPv3 0)
  set(_NO_SNMPv3 1)
endif()

if(SNMP_PP_IPv6)
  set(WITH_SNMP_PP_IPv6 1)
  set(SNMP_PP_IPv6 1)
else()
  set(WITH_SNMP_PP_IPv6 0)
  set(SNMP_PP_IPv6 0)
endif()

if(SNMP_PP_THREADS)
  set(CMAKE_THREAD_PREFER_PTHREAD 1)
  find_package(Threads REQUIRED)

  set(WITH_THREADS 1)
  if(CNF_HAVE_PTHREAD_H)
    set(WITH_PTHREAD 1)
  else()
    set(WITH_PTHREAD 0)
  endif()
else()
  set(CMAKE_DISABLE_FIND_PACKAGE_Threads ON)
  set(WITH_THREADS 0)
  set(WITH_PTHREAD 0)
endif()

if(SNMP_PP_NAMESPACE)
  set(WITH_NAMESPACE 1)
else()
  message(FATAL_ERROR "NO NAMESPACE?")
  set(WITH_NAMESPACE 0)
endif()

if(SNMP_PP_LOGGING)
  set(WITH_LOGGING 1)
else()
  set(WITH_LOGGING 0)
endif()

if(SNMP_PP_MACADDR)
  set(WITH_MACADDRESS 1)
else()
  set(WITH_MACADDRESS 0)
endif()

if(SNMP_PP_IPXADDR)
  set(WITH_IPXADDRESS 1)
else()
  set(WITH_IPXADDRESS 0)
endif()

if(SNMP_PP_EXTENDED_DEBUG)
  set(_DEBUG 1)
else()
  set(_DEBUG 0)
endif()

option(USE_OUTPUT_PATH "build all libaries and runtime files at the bin directory" YES)
if(USE_OUTPUT_PATH)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

# ---- Add dependencies via CPM ----
# see https://github.com/cpm-cmake/CPM.cmake for more info

include(CPM)

CPMAddPackage("gh:aminya/project_options@0.32.2")
list(APPEND CMAKE_MODULE_PATH ${ProjectOptions_SRC_DIR})

if(SNMP_PP_OPENSSL)
  if(APPLE)
    # NOTE: may needed on OSX! CK
    set(OPENSSL_ROOT_DIR
        /usr/local/opt/openssl
        CACHE FILEPATH ""
    )
  endif()

  find_package(OpenSSL)

  if(OPENSSL_FOUND)
    message(STATUS "Found OpenSSL (include: ${OPENSSL_INCLUDE_DIR}, library: ${OPENSSL_LIBRARIES})")
    set(CRYPTO_INCLUDE_DIRS ${OPENSSL_INCLUDE_DIR})
    set(CRYPTO_LINKLIBS ${OPENSSL_LIBRARIES})
    set(CRYPTO_LIB OpenSSL)
    set(WITH_LIBSSL 1)
  else()
    # message(FATAL_ERROR "LibOpenSSL NOT found!")
    set(WITH_LIBSSL 0)
  endif()
else()
  set(WITH_LIBSSL 0)
endif()

if(NOT CRYPTO_LIB AND SNMP_PP_LIBTOMCRYPT)
  find_package(TOMCRYPT)

  if(TOMCRYPT_FOUND)
    set(WITH_LIBSSL 0)

    message(STATUS "Found TOMCRYPT (include: ${TOMCRYPT_INCLUDE_DIR}, library: ${TOMCRYPT_LIBRARIES})")
    set(CRYPTO_INCLUDE_DIRS ${TOMCRYPT_INCLUDE_DIR})
    set(CRYPTO_LINKLIBS ${TOMCRYPT_LIBRARIES})
    set(CRYPTO_LIB TOMCRYPT)
    set(WITH_LIBTOMCRYPT 1)
  else()
    # message(FATAL_ERROR "Libtomcrypt NOT found!")
    set(WITH_LIBTOMCRYPT 0)
  endif()

else()
  set(WITH_LIBTOMCRYPT 0)
endif()

if(NOT CRYPTO_LIB AND SNMP_PP_LIBDES)
  # see https://github.com/ClausKlein/libdes/releases/tag/v4.1.1.2
  CPMAddPackage(
    NAME libdes
    GIT_TAG v4.1.1.2
    GITHUB_REPOSITORY ClausKlein/libdes
  )
  set(WITH_LIBSSL 0)
  set(WITH_LIBTOMCRYPT 0)

  set(CRYPTO_INCLUDE_DIRS ${des_SOURCE_DIR})
  set(CRYPTO_LINKLIBS des::des)

  set(CRYPTO_LIB des)
  set(WITH_LIBDES 1)
else()
  set(WITH_LIBDES 0)
endif()

if(SNMP_PP_LOGGING)
  if(${LogProfile} STREQUAL "off")
    set(WITH_LOG_PROFILES 0)
  else()
    set(WITH_LOG_PROFILES 1)
    set(DEFAULT_LOG_PROFILE "${LogProfile}")
  endif()
else()
  set(WITH_LOG_PROFILES 0)
endif()

if(CNF_STDC_HEADERS)
  set(STDC_HEADERS 1)
else()
  set(STDC_HEADERS 0)
endif()

if(CNF_STDCXX_98_HEADERS)
  set(STDCXX_98_HEADERS 1)
  set(STDC_HEADERS 0)
else()
  set(STDCXX_98_HEADERS 0)
endif()

check_type_size(size_t SIZE_T LANGUAGE CXX)
if(NOT HAVE_SIZE_T)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
    set(size_t "uint64_t")
  else()
    set(size_t "uint32_t")
  endif("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
endif()

check_include_files("sys/mount.h" HAVE_SYS_MOUNT_H)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.h.in config.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake_libsnmp.h.in libsnmp.h)
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/snmp_pp/config_snmp_pp.h.in
  ${CMAKE_CURRENT_SOURCE_DIR}/include/snmp_pp/config_snmp_pp.h
)

set(MY_HEADER_FILES
    include/snmp_pp/address.h
    include/snmp_pp/asn1.h
    include/snmp_pp/auth_priv.h
    include/snmp_pp/collect.h
    include/snmp_pp/config_snmp_pp.h
    include/snmp_pp/counter.h
    include/snmp_pp/ctr64.h
    include/snmp_pp/eventlist.h
    include/snmp_pp/eventlistholder.h
    include/snmp_pp/gauge.h
    include/snmp_pp/idea.h
    include/snmp_pp/integer.h
    include/snmp_pp/IPv6Utility.h
    include/snmp_pp/log.h
    include/snmp_pp/md5.h
    include/snmp_pp/mp_v3.h
    include/snmp_pp/msec.h
    include/snmp_pp/msgqueue.h
    include/snmp_pp/notifyqueue.h
    include/snmp_pp/octet.h
    include/snmp_pp/oid.h
    include/snmp_pp/oid_def.h
    include/snmp_pp/pdu.h
    include/snmp_pp/reentrant.h
    include/snmp_pp/sha.h
    include/snmp_pp/smi.h
    include/snmp_pp/smival.h
    include/snmp_pp/snmp_pp.h
    include/snmp_pp/snmperrs.h
    include/snmp_pp/snmpmsg.h
    include/snmp_pp/target.h
    include/snmp_pp/timetick.h
    include/snmp_pp/userdefined.h
    include/snmp_pp/usertimeout.h
    include/snmp_pp/usm_v3.h
    include/snmp_pp/uxsnmp.h
    include/snmp_pp/v3.h
    include/snmp_pp/vb.h
)

set(MY_HEADER_LIB_FILES ${CMAKE_CURRENT_BINARY_DIR}/libsnmp.h)

set(MY_SRC_FILES
    src/address.cpp
    src/asn1.cpp
    src/auth_priv.cpp
    src/counter.cpp
    src/ctr64.cpp
    src/eventlist.cpp
    src/eventlistholder.cpp
    src/gauge.cpp
    src/idea.cpp
    src/integer.cpp
    src/IPv6Utility.cpp
    src/log.cpp
    src/md5c.cpp
    src/mp_v3.cpp
    src/msec.cpp
    src/msgqueue.cpp
    src/notifyqueue.cpp
    src/octet.cpp
    src/oid.cpp
    src/pdu.cpp
    src/reentrant.cpp
    src/sha.cpp
    src/snmpmsg.cpp
    src/target.cpp
    src/timetick.cpp
    src/userdefined.cpp
    src/usertimeout.cpp
    src/usm_v3.cpp
    src/uxsnmp.cpp
    src/v3.cpp
    src/vb.cpp
)

option(BUILD_SHARED_LIBS "Global flag to cause add_library() to create shared libraries if on." YES)

if(APPLE)
  set(OPTION_ENABLED_SANITIZER
      "ENABLE_SANITIZER_ADDRESS; ENABLE_SANITIZER_UNDEFINED_BEHAVIOR"
      CACHE STRING "Enabled sanitizer for debug build"
  )
else()
  set(OPTION_ENABLED_SANITIZER
      "ENABLE_SANITIZER_MEMORY"
      CACHE STRING "Enabled sanitizer for debug build"
  )
endif()
option(OPTION_ENABLE_COVERAGE "Enable test coverage of projects" OFF)
if(OPTION_ENABLE_COVERAGE)
  set(ENABLE_COVERAGE "ENABLE_COVERAGE")
endif()

if(SNMP_PP_LOGGING)
  set(OPTION_ENABLE_UNITY
      OFF
      CACHE STRING "forced" FORCE
  )
else()
  option(OPTION_ENABLE_UNITY "Enable Unity builds of projects" ON)
endif()

if(OPTION_ENABLE_UNITY)
  set(ENABLE_UNITY "ENABLE_UNITY")
endif()

project_options(
  PREFIX
  ${PROJECT_NAME}
  ENABLE_CACHE
  ${ENABLE_COVERAGE}
  ${OPTION_ENABLED_SANITIZER}
  #XXX ENABLE_SANITIZER_ADDRESS
  #XXX ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
  #XXX ENABLE_SANITIZER_THREAD
  #XXX ENABLE_SANITIZER_MEMORY
  # TODO: WARNINGS_AS_ERRORS
)

set(PROJECT_EXPORT_HEADER ${PROJECT_NAME}/export.h)
add_library(${PROJECT_NAME} ${MY_HEADER_FILES} ${MY_HEADER_LIB_FILES} ${CMAKE_CURRENT_BINARY_DIR}/config.h ${MY_SRC_FILES})

if(CMAKE_SKIP_INSTALL_RULES)
  include(GenerateExportHeader)
  generate_export_header(
    ${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/PackageProjectInclude/${PROJECT_EXPORT_HEADER}
  )
  add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
  target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_project_options ${PROJECT_NAME}_project_warnings)

  # target_link_libraries(
  #   ${PROJECT_NAME} PRIVATE $<BUILD_LOCAL_INTERFACE:${PROJECT_NAME}_project_options>
  #                           $<BUILD_LOCAL_INTERFACE:${PROJECT_NAME}_project_warnings>
  # )
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ${OPTION_ENABLE_UNITY})

if(MSVC)
  target_link_libraries(${PROJECT_NAME} PUBLIC wsock32 ws2_32)
  target_compile_definitions(${PROJECT_NAME} PUBLIC WIN32)
  target_compile_options(${PROJECT_NAME} PRIVATE /W3 /wd4251)
  target_compile_definitions(${PROJECT_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS)
else()
  target_compile_options(
    ${PROJECT_NAME} PUBLIC -Wno-conversion -Wshadow -Wno-unused-parameter -Wno-deprecated-declarations -Wno-old-style-cast
                           -Wno-extra-semi
  )
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)
set_target_properties(
  ${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}
                             SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})
target_link_libraries(${PROJECT_NAME} PUBLIC ${CRYPTO_LINKLIBS} Threads::Threads)
target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_CONFIG_H)

#
# NOTE: we have to prevent the use of older installed project headers
#
target_include_directories(
  ${PROJECT_NAME} SYSTEM BEFORE PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/PackageProjectInclude> $<BUILD_INTERFACE:${CRYPTO_INCLUDE_DIRS}>
         $<INSTALL_INTERFACE:include>
)

# Note: for SameMajorVersion upgrade stategy
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR}
             VERSION ${PROJECT_VERSION}
             VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
             CMAKE_VISIBILITY_INLINES_HIDDEN ${BUILD_SHARED_LIBS}
)

if(SNMP_PP_EXAMPLES)
  set(EXAMPLE_SOURCE_FILES
      # consoleExamples/receive_trap.cpp
      # consoleExamples/snmpBulk.cpp
      # consoleExamples/snmpDiscover.cpp
      # consoleExamples/snmpGet.cpp
      # consoleExamples/snmpInform.cpp
      # consoleExamples/snmpNext.cpp
      # consoleExamples/snmpNextAsync.cpp
      # consoleExamples/snmpPasswd.cpp
      # consoleExamples/snmpSet.cpp
      # consoleExamples/snmpTraps.cpp
      # consoleExamples/snmpWalk.cpp
      consoleExamples/test_app.cpp
  )

  if(NOT MSVC)
    # list(APPEND EXAMPLE_SOURCE_FILES consoleExamples/snmpWalkThreads.cpp)
  endif()

  foreach(examplesourcefile ${EXAMPLE_SOURCE_FILES})
    string(REPLACE ".cpp" "" examplename ${examplesourcefile})
    string(REPLACE "consoleExamples/" "" examplename ${examplename})
    add_executable(${examplename} ${examplesourcefile})
    target_link_libraries(${examplename} ${PROJECT_NAME})
    #    target_include_directories(
    #      ${examplename} SYSTEM BEFORE PRIVATE ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include
    #    )
  endforeach()

  enable_testing()
  add_test(NAME test_app COMMAND test_app 127.0.0.1 trap)
  add_test(NAME send_trap COMMAND test_app localhost trap)
  add_test(NAME env_test COMMAND ${CMAKE_COMMAND} -E echo $ENV{CMAKE_CONFIG_TYPE})
  add_test(NAME basename_test COMMAND ${CMAKE_COMMAND} -E echo $<TARGET_FILE_DIR:test_app>)
endif()

if(CMAKE_SKIP_INSTALL_RULES)
  return()
endif()

install(FILES ${MY_HEADER_LIB_FILES} DESTINATION include)

CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.11.0")
packageProject(
  # the name of the target to export
  NAME ${PROJECT_NAME}
  # the version of the target to export
  VERSION ${PROJECT_VERSION}
  # a temporary directory to create the config files
  BINARY_DIR ${PROJECT_BINARY_DIR}
  # location of the target's public headers
  INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include
  # should match the target's INSTALL_INTERFACE include directory
  INCLUDE_DESTINATION include
  # (optional) option to install only header files with matching pattern
  INCLUDE_HEADER_PATTERN "*.h"
  # semicolon separated list of the project's dependencies
  DEPENDENCIES "${CRYPTO_LIB}; Threads"
  # (optional) create a header containing the version info
  # Note: that the path to headers should be lowercase
  VERSION_HEADER "${PROJECT_NAME}/version.h"
  # (optional) create a export header using GenerateExportHeader module
  EXPORT_HEADER "${PROJECT_EXPORT_HEADER}"
  # (optional) install your library with a namespace (Note: do NOT add extra '::')
  NAMESPACE ${PROJECT_NAME}
  # (optional) define the project's version compatibility, defaults to `AnyNewerVersion`
  # supported values: `AnyNewerVersion|SameMajorVersion|SameMinorVersion|ExactVersion`
  COMPATIBILITY SameMajorVersion
  # (optional) option to disable the versioning of install destinations
  DISABLE_VERSION_SUFFIX YES
  # (optional) option to ignore target architecture for package resolution
  # defaults to YES for header only (i.e. INTERFACE) libraries
  ## ARCH_INDEPENDENT YES
)
