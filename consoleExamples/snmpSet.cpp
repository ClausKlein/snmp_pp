/*_############################################################################
 * _##
 * _##  snmpSet.cpp
 * _##
 * _##  SNMP++ v3.4
 * _##  -----------------------------------------------
 * _##  Copyright (c) 2001-2021 Jochen Katz, Frank Fock
 * _##
 * _##  This software is based on SNMP++2.6 from Hewlett Packard:
 * _##
 * _##    Copyright (c) 1996
 * _##    Hewlett-Packard Company
 * _##
 * _##  ATTENTION: USE OF THIS SOFTWARE IS SUBJECT TO THE FOLLOWING TERMS.
 * _##  Permission to use, copy, modify, distribute and/or sell this software
 * _##  and/or its documentation is hereby granted without fee. User agrees
 * _##  to display the above copyright notice and this license notice in all
 * _##  copies of the software and any documentation of the software. User
 * _##  agrees to assume all liability for the use of the software;
 * _##  Hewlett-Packard, Frank Fock, and Jochen Katz make no representations
 * _##  about the suitability of this software for any purpose. It is provided
 * _##  "AS-IS" without warranty of any kind, either express or implied. User
 * _##  hereby grants a royalty-free license to any and all derivatives based
 * _##  upon this software code base.
 * _##
 * _##########################################################################*/
/*
 * snmpSet.cpp
 *
 * Copyright (c) 1996
 * Hewlett-Packard Company
 *
 * ATTENTION: USE OF THIS SOFTWARE IS SUBJECT TO THE FOLLOWING TERMS.
 * Permission to use, copy, modify, distribute and/or sell this software
 * and/or its documentation is hereby granted without fee. User agrees
 * to display the above copyright notice and this license notice in all
 * copies of the software and any documentation of the software. User
 * agrees to assume all liability for the use of the software; Hewlett-Packard
 * makes no representations about the suitability of this software for any
 * purpose. It is provided "AS-IS" without warranty of any kind,either express
 * or implied. User hereby grants a royalty-free license to any and all
 * derivatives based upon this software code base.
 *
 * Peter E. Mellquist
 */

#include "snmp_pp/snmp_pp.h"

#include <libsnmp.h>

#ifdef SNMP_PP_NAMESPACE
using namespace Snmp_pp;
#endif

// determine the smi type and get a value from the user
bool determine_vb(SmiUINT32 val, Vb& vb)
{
    char buffer[255];

    if (val == sNMP_SYNTAX_NOSUCHINSTANCE)
    {
        std::cout << "Instance does not exists but can be created.\n";
        std::cout << "Please enter one of the following types:\n\n";
        std::cout << "Integer:  " << sNMP_SYNTAX_INT << "\n";
        std::cout << "Bits:     " << sNMP_SYNTAX_BITS << "\n";
        std::cout << "STRING:   " << sNMP_SYNTAX_OCTETS << "\n";
        std::cout << "Oid:      " << sNMP_SYNTAX_OID << "\n";
        std::cout << "IpAddress:" << sNMP_SYNTAX_IPADDR << "\n\n";
        std::cout << "Please choose value type: ";
        std::cin >> val;
        vb.set_syntax(val);
    }
    std::cout << "Value Type is ";

    switch (val)
    {
    // octet string
    case sNMP_SYNTAX_OCTETS: {
        std::cout << "Octet String\n";
        std::cout << "Please enter new value: ";
        std::cin >> buffer;
        OctetStr octetstr(buffer);
        if (octetstr.valid())
        {
            vb.set_value(octetstr);
            return true;
        }
        else
        {
            std::cout << "Invalid OctetStr\n";
            return false;
        }
    }

    // IP Address
    case sNMP_SYNTAX_IPADDR: {
        std::cout << "IP Address\n";
        std::cout << "Please enter new value: ";
        std::cin >> buffer;
        IpAddress ipaddress(buffer);
        if (ipaddress.valid())
        {
            vb.set_value(ipaddress);
            return true;
        }
        else
        {
            std::cout << "Invalid IP Address\n";
            return false;
        }
    }

    // Oid
    case sNMP_SYNTAX_OID: {
        std::cout << "Oid\n";
        std::cout << "Please enter new value: ";
        std::cin >> buffer;
        Oid oid(buffer);
        if (oid.valid())
        {
            vb.set_value(oid);
            return true;
        }
        else
        {
            std::cout << "Invalid Oid\n";
            return false;
        }
    }

    // TimeTicks
    case sNMP_SYNTAX_TIMETICKS: {
        std::cout << "TimeTicks\n";
        std::cout << "Please enter new value: ";
        std::cin >> buffer;
        uint32_t i;
        i = atol(buffer);
        TimeTicks timeticks(i);
        if (timeticks.valid())
        {
            vb.set_value(timeticks);
            return true;
        }
        else
        {
            std::cout << "Invalid TimeTicks\n";
            return false;
        }
    }

    // Gauge32
    case sNMP_SYNTAX_GAUGE32: {
        std::cout << "Gauge32\n";
        std::cout << "Please enter new value: ";
        std::cin >> buffer;
        uint32_t i;
        i = atol(buffer);
        Gauge32 gauge32(i);
        if (gauge32.valid())
        {
            vb.set_value(gauge32);
            return true;
        }
        else
        {
            std::cout << "Invalid Gauge32\n";
            return false;
        }
    }

    case sNMP_SYNTAX_CNTR32: {
        std::cout << "Counter32\n";
        std::cout << "Please enter new value: ";
        std::cin >> buffer;
        uint32_t i;
        i = atol(buffer);
        Counter32 counter32(i);
        if (counter32.valid())
        {
            vb.set_value(counter32);
            return true;
        }
        else
        {
            std::cout << "Invalid Counter32\n";
            return false;
        }
    }

    case sNMP_SYNTAX_CNTR64: {
        std::cout << "Counter64\n";
        std::cout << "Please enter value (low 32 bit): ";
        std::cin >> buffer;
        uint32_t i;
        i = atol(buffer);
        Counter64 counter64;
        counter64.set_low(i);

        std::cout << "Please enter value (high 32 bit): ";
        std::cin >> buffer;
        i = atol(buffer);
        counter64.set_high(i);

        if (counter64.valid())
        {
            vb.set_value(counter64);
            return true;
        }
        else
        {
            std::cout << "Invalid Counter64\n";
            return false;
        }
    }

    case sNMP_SYNTAX_INT: {
        std::cout << "Integer\n";
        std::cout << "Please enter new value: ";
        std::cin >> buffer;
        uint32_t i;
        i = atol(buffer);
        long l;
        l = (long)i;
        vb.set_value(l);
        return true;
    }

    case sNMP_SYNTAX_NOSUCHOBJECT: {
        std::cout << "NO SUCH OBJECT\n";
        std::cout << "Object cannot be created.\n";
        return false;
    }

    default: {
        std::cout << "Unknown Data Type " << val << "\n";
        return false;
    }
    }
}

static void usage()
{
    std::cout << "Usage:\n";
    std::cout << "snmpSet IpAddress | DNSName [Oid] [options]\n";
    exit(1);
}

static void help()
{
    std::cout << "Usage:\n";
    std::cout << "snmpSet IpAddress | DNSName [Oid] [options]\n";
    std::cout << "Oid: sysDescr object is default\n";
    std::cout << "options: -vN , use SNMP version 1, 2 or 3, default is 1\n";
    std::cout << "         -PPort , remote port to use\n";
    std::cout << "         -CCommunity_name, specify SET community default is "
                 "'public' \n";
    std::cout << "         -GCommunity_name, specify GET community default is "
                 "set community value \n";
    std::cout << "         -rN , retries default is N = 1 retry\n";
    std::cout << "         -tN , timeout in hundredths of seconds; default is "
                 "N = 100\n";
#ifdef _SNMPv3
    std::cout << "         -snSecurityName, \n";
    std::cout
        << "         -slN , securityLevel to use, default N = 3 = authPriv\n";
    std::cout << "         -smN , securityModel to use, only default N = 3 = "
                 "USM possible\n";
    std::cout << "         -cnContextName, default empty string\n";
    std::cout << "         -ceContextEngineID, as hex e.g. 800007E580, "
                 "default empty string\n";
    std::cout << "         -authPROT, use authentication protocol NONE, SHA "
                 "or MD5\n";
    std::cout << "         -privPROT, use privacy protocol NONE, DES, "
                 "3DESEDE, IDEA, AES128, AES192 or AES256\n";
    std::cout << "         -uaAuthPassword\n";
    std::cout << "         -upPrivPassword\n";
#endif
#ifdef WITH_LOG_PROFILES
    std::cout << "         -Lprofile , log profile to use, default is '"
#    ifdef DEFAULT_LOG_PROFILE
              << DEFAULT_LOG_PROFILE
#    else
              << "original"
#    endif
              << "'\n";
#endif
    std::cout << "         -h, -? - prints this help\n";
    exit(1);
}

int main(int argc, char** argv)
{
    //---------[ check the arg count ]----------------------------------------
    if (argc < 2)
    {
        usage();
    }
    if (strstr(argv[1], "-h") != 0)
    {
        help();
    }
    if (strstr(argv[1], "-?") != 0)
    {
        usage();
    }

#if !defined(_NO_LOGGING) && !defined(WITH_LOG_PROFILES)
    // Set filter for logging
    DefaultLog::log()->set_filter(ERROR_LOG, 7);
    DefaultLog::log()->set_filter(WARNING_LOG, 7);
    DefaultLog::log()->set_filter(EVENT_LOG, 7);
    DefaultLog::log()->set_filter(INFO_LOG, 7);
    DefaultLog::log()->set_filter(DEBUG_LOG, 7);
#endif

    Snmp::socket_startup(); // Initialize socket subsystem

    //---------[ make a GenAddress and Oid object to retrieve ]---------------
    UdpAddress address(argv[1]); // make a SNMP++ Generic address
    if (!address.valid())
    {                            // check validity of address
        std::cout << "Invalid Address or DNS Name, " << argv[1] << "\n";
        usage();
    }
    Oid oid("1.3.6.1.2.1.1.4.0"); // default is sysName
    int oid_count = 0;
    if (argc >= 3)
    {                             // if 3 args, then use the callers Oid
        if (strstr(argv[2], "-") == 0)
        {
            oid = argv[2];
            oid_count++;
            if (!oid.valid())
            { // check validity of user oid
                std::cout << "Invalid Oid, " << argv[2] << "\n";
                usage();
            }
        }
    }

    //---------[ determine options to use ]-----------------------------------
    snmp_version version = version1;  // default is v1
    int          retries = 1;         // default retries is 1
    int          timeout = 100;       // default is 1 second
    u_short      port    = 161;       // default snmp port is 161
    OctetStr     community("public"); // community name
    OctetStr     get_community;

#ifdef _SNMPv3
    OctetStr privPassword("");
    OctetStr authPassword("");
    OctetStr securityName("");
    int      securityModel = SNMP_SECURITY_MODEL_USM;
    int      securityLevel = SNMP_SECURITY_LEVEL_AUTH_PRIV;
    OctetStr contextName("");
    OctetStr contextEngineID("");
    long     authProtocol = SNMP_AUTHPROTOCOL_NONE;
    long     privProtocol = SNMP_PRIVPROTOCOL_NONE;
    v3MP*    v3_MP;
#endif

    char* ptr;

    for (int x = 2 + oid_count; x < argc; x++)
    { // parse for version
        if (strstr(argv[x], "-v2") != 0)
        {
            version = version2c;
            continue;
        }
        if (strstr(argv[x], "-v1") != 0)
        {
            version = version1;
            continue;
        }
        if (strstr(argv[x], "-r") != 0)
        { // parse for retries
            ptr = argv[x];
            ptr++;
            ptr++;
            retries = atoi(ptr);
            if ((retries < 0) || (retries > 5))
            {
                retries = 1;
            }
            continue;
        }
        if (strstr(argv[x], "-t") != 0)
        { // parse for timeout
            ptr = argv[x];
            ptr++;
            ptr++;
            timeout = atoi(ptr);
            if ((timeout < 100) || (timeout > 500))
            {
                timeout = 100;
            }
            continue;
        }
        if (strstr(argv[x], "-C") != 0)
        {
            ptr = argv[x];
            ptr++;
            ptr++;
            community = ptr;
            continue;
        }
        if (strstr(argv[x], "-G") != 0)
        {
            ptr = argv[x];
            ptr++;
            ptr++;
            get_community = ptr;
            continue;
        }
        if (strstr(argv[x], "-P") != 0)
        {
            ptr = argv[x];
            ptr++;
            ptr++;
            sscanf(ptr, "%hu", &port);
            continue;
        }

#ifdef WITH_LOG_PROFILES
        if (strstr(argv[x], "-L") != 0)
        {
            ptr = argv[x];
            ptr++;
            ptr++;
            DefaultLog::log()->set_profile(ptr);
            continue;
        }
#endif

#ifdef _SNMPv3
        if (strstr(argv[x], "-v3") != 0)
        {
            version = version3;
            continue;
        }
        if (strstr(argv[x], "-auth") != 0)
        {
            ptr = argv[x];
            ptr += 5;
            if (strcasecmp(ptr, "SHA") == 0)
            {
                authProtocol = SNMP_AUTHPROTOCOL_HMACSHA;
            }
            else if (strcasecmp(ptr, "MD5") == 0)
            {
                authProtocol = SNMP_AUTHPROTOCOL_HMACMD5;
            }
            else if (strcasecmp(ptr, "NONE") == 0)
            {
                authProtocol = SNMP_AUTHPROTOCOL_NONE;
            }
            else
            {
                std::cout << "Warning: ignoring unknown auth protocol: " << ptr
                          << std::endl;
            }
            continue;
        }
        if (strstr(argv[x], "-priv") != 0)
        {
            ptr = argv[x];
            ptr += 5;
            if (strcasecmp(ptr, "DES") == 0)
            {
                privProtocol = SNMP_PRIVPROTOCOL_DES;
            }
            else if (strcasecmp(ptr, "3DESEDE") == 0)
            {
                privProtocol = SNMP_PRIVPROTOCOL_3DESEDE;
            }
            else if (strcasecmp(ptr, "IDEA") == 0)
            {
                privProtocol = SNMP_PRIVPROTOCOL_IDEA;
            }
            else if (strcasecmp(ptr, "AES128") == 0)
            {
                privProtocol = SNMP_PRIVPROTOCOL_AES128;
            }
            else if (strcasecmp(ptr, "AES192") == 0)
            {
                privProtocol = SNMP_PRIVPROTOCOL_AES192;
            }
            else if (strcasecmp(ptr, "AES256") == 0)
            {
                privProtocol = SNMP_PRIVPROTOCOL_AES256;
            }
            else if (strcasecmp(ptr, "NONE") == 0)
            {
                privProtocol = SNMP_PRIVPROTOCOL_NONE;
            }
            else
            {
                std::cout << "Warning: ignoring unknown priv protocol: " << ptr
                          << std::endl;
            }
            continue;
        }
        if (strstr(argv[x], "-sn") != 0)
        {
            ptr = argv[x];
            ptr += 3;
            securityName = ptr;
            continue;
        }
        if (strstr(argv[x], "-sl") != 0)
        {
            ptr = argv[x];
            ptr += 3;
            securityLevel = atoi(ptr);
            if ((securityLevel < SNMP_SECURITY_LEVEL_NOAUTH_NOPRIV)
                || (securityLevel > SNMP_SECURITY_LEVEL_AUTH_PRIV))
            {
                securityLevel = SNMP_SECURITY_LEVEL_AUTH_PRIV;
            }
            continue;
        }
        if (strstr(argv[x], "-sm") != 0)
        {
            ptr = argv[x];
            ptr += 3;
            securityModel = atoi(ptr);
            if ((securityModel < SNMP_SECURITY_MODEL_V1)
                || (securityModel > SNMP_SECURITY_MODEL_USM))
            {
                securityModel = SNMP_SECURITY_MODEL_USM;
            }
            continue;
        }
        if (strstr(argv[x], "-cn") != 0)
        {
            ptr = argv[x];
            ptr += 3;
            contextName = ptr;
            continue;
        }
        if (strstr(argv[x], "-ce") != 0)
        {
            ptr = argv[x];
            ptr += 3;
            contextEngineID = OctetStr::from_hex_string(ptr);
            continue;
        }
        if (strstr(argv[x], "-ua") != 0)
        {
            ptr = argv[x];
            ptr += 3;
            authPassword = ptr;
            continue;
        }
        if (strstr(argv[x], "-up") != 0)
        {
            ptr = argv[x];
            ptr += 3;
            privPassword = ptr;
            continue;
        }
#endif

        std::cout << "Error: unknown parameter: " << argv[x] << "\n";
        usage();
    }

    if (get_community.len() == 0)
    {
        get_community = community;
    }

    //----------[ create a SNMP++ session ]-----------------------------------
    int status;
    // bind to any port and use IPv6 if needed
    Snmp snmp(status, 0, (address.get_ip_version() == Address::version_ipv6));

    if (status != SNMP_CLASS_SUCCESS)
    {
        std::cout << "SNMP++ Session Create Fail, " << snmp.error_msg(status)
                  << "\n";
        return 1;
    }

    //---------[ init SnmpV3 ]--------------------------------------------
#ifdef _SNMPv3
    if (version == version3)
    {
        const char*  engineId        = "snmpSet";
        const char*  filename        = "snmpv3_boot_counter";
        unsigned int snmpEngineBoots = 0;
        int          status;

        status = getBootCounter(filename, engineId, snmpEngineBoots);
        if ((status != SNMPv3_OK) && (status < SNMPv3_FILEOPEN_ERROR))
        {
            std::cout << "Error loading snmpEngineBoots counter: " << status
                      << std::endl;
            return 1;
        }
        snmpEngineBoots++;
        status = saveBootCounter(filename, engineId, snmpEngineBoots);
        if (status != SNMPv3_OK)
        {
            std::cout << "Error saving snmpEngineBoots counter: " << status
                      << std::endl;
            return 1;
        }

        int construct_status;
        v3_MP = new v3MP(engineId, snmpEngineBoots, construct_status);
        if (construct_status != SNMPv3_MP_OK)
        {
            std::cout << "Error initializing v3MP: " << construct_status
                      << std::endl;
            return 1;
        }

        USM* usm = v3_MP->get_usm();
        usm->add_usm_user(securityName, authProtocol, privProtocol,
            authPassword, privPassword);
    }
    else
    {
        // MUST create a dummy v3MP object if _SNMPv3 is enabled!
        int construct_status;
        v3_MP = new v3MP("dummy", 0, construct_status);
    }

    snmp.set_mpv3(v3_MP); // must be set since 3.4.0
#endif

    //--------[ build up SNMP++ object needed ]-------------------------------
    Pdu pdu;                  // construct a Pdu object
    Vb  vb;                   // construct a Vb object
    vb.set_oid(oid);          // set the Oid portion of the Vb
    pdu += vb;                // add the vb to the Pdu

    address.set_port(port);
    CTarget ctarget(address); // make a target using the address
#ifdef _SNMPv3
    UTarget utarget(address);

    if (version == version3)
    {
        utarget.set_version(
            version);               // set the SNMP version SNMPV1 or V2 or V3
        utarget.set_retry(retries); // set the number of auto retries
        utarget.set_timeout(timeout); // set timeout
        utarget.set_security_model(securityModel);
        utarget.set_security_name(securityName);
        pdu.set_security_level(securityLevel);
        pdu.set_context_name(contextName);
        pdu.set_context_engine_id(contextEngineID);
    }
    else
    {
#endif
        ctarget.set_version(version); // set the SNMP version SNMPV1 or V2
        ctarget.set_retry(retries);   // set the number of auto retries
        ctarget.set_timeout(timeout); // set timeout
        ctarget.set_readcommunity(
            get_community);           // set the read community name
        ctarget.set_writecommunity(community); // set the write community name
#ifdef _SNMPv3
    }
#endif
    //-------[ issue the request, blocked mode ]-----------------------------
    std::cout << "SNMP++ Set to " << argv[1] << " SNMPV"
#ifdef _SNMPv3
              << ((version == version3) ? (version) : (version + 1))
#else
              << (version + 1)
#endif
              << " Retries=" << retries << " Timeout=" << timeout * 10 << "ms";
#ifdef _SNMPv3
    if (version == version3)
    {
        std::cout << std::endl
                  << "securityName= " << securityName.get_printable()
                  << ", securityLevel= " << securityLevel
                  << ", securityModel= " << securityModel << std::endl
                  << "contextName= " << contextName.get_printable()
                  << ", contextEngineID= " << contextEngineID.get_printable()
                  << std::endl;
    }
    else
#endif
        std::cout << " SET-community=" << community.get_printable()
                  << " GET-community=" << get_community.get_printable()
                  << std::endl
                  << std::flush;

    SnmpTarget* target;
#ifdef _SNMPv3
    if (version == version3)
    {
        target = &utarget;
    }
    else
#endif
        target = &ctarget;

    // first get the variabel to determine its type
    if ((status = snmp.get(pdu, *target)) == SNMP_CLASS_SUCCESS)
    {
        pdu.get_vb(vb, 0);
        std::cout << "Oid = " << vb.get_printable_oid() << std::endl
                  << "Current Value = " << vb.get_printable_value()
                  << std::endl;
#ifdef _SNMPv3
        if (pdu.get_type() == REPORT_MSG)
        {
            std::cout << "Received a reportPdu: "
                      << snmp.error_msg(vb.get_printable_oid()) << std::endl
                      << vb.get_printable_oid() << " = "
                      << vb.get_printable_value() << std::endl;
            return -5;
        }
#endif
        if (determine_vb(vb.get_syntax(), vb))
        {
            // do the Set
            Pdu setpdu;

#ifdef _SNMPv3
            setpdu.set_security_level(securityLevel);
            setpdu.set_context_name(contextName);
            setpdu.set_context_engine_id(contextEngineID);
#endif

            vb.set_oid(oid); // use the same oid as the inquire
            setpdu += vb;
            status = snmp.set(setpdu, *target);
            std::cout << "Set Status = " << snmp.error_msg(status) << "\n";
        }
    }
    else
    {
        std::cout << "SNMP++ Set Error, " << snmp.error_msg(status) << "\n";
    }

    Snmp::socket_cleanup(); // Shut down socket subsystem
}
