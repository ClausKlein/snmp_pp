/*_############################################################################
 * _##
 * _##  counter.cpp
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
/*===================================================================
 *
 * Copyright (c) 1999
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
 * C O U N T E R. C P P
 *
 * COUNTER32 CLASS IMPLEMENTATION
 *
 * DESIGN + AUTHOR:  Peter E Mellquist
 *
 * DESCRIPTION:
 * Class implementation for SMI Counter32 class.
 * =====================================================================*/

#include "snmp_pp/counter.h"

#include <libsnmp.h>

#ifdef SNMP_PP_NAMESPACE
namespace Snmp_pp
{
#endif

#if 0
// general assignment from any Value
SnmpSyntax& Counter32::operator=(const SnmpSyntax&in_val)
{
    if (this == &in_val)
    {
        return *this;           // handle assignement from itself
    }
    valid_flag = false;         // will get set true if really valid
    if (in_val.valid())
    {
        switch (in_val.get_syntax())
        {
        case sNMP_SYNTAX_UINT32:
        // case sNMP_SYNTAX_GAUGE32:        .. indistinquishable from UINT32
        case sNMP_SYNTAX_CNTR32:
        case sNMP_SYNTAX_TIMETICKS:
        case sNMP_SYNTAX_INT32: {       // implied cast int -> uint
            smival.value.uNumber = ((Counter32&)in_val).smival.value.uNumber;
            valid_flag           = true;
            break;
        }
        }
    }
    m_changed = true;
    return *this;
}

#endif

#ifdef SNMP_PP_NAMESPACE
} // end of namespace Snmp_pp
#endif
