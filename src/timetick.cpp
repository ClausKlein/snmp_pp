/*_############################################################################
 * _##
 * _##  timetick.cpp
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
 * T I M E T I C K. C P P
 *
 * TIMETICK CLASS IMPLEMENTATION
 *
 * DESIGN + AUTHOR:  Peter E Mellquist
 *
 * DESCRIPTION:
 * Class implentation for SMI Timeticks class.
 * =====================================================================*/

#include "snmp_pp/timetick.h" // include header file for timetick class

#include <libsnmp.h>

#ifdef SNMP_PP_NAMESPACE
namespace Snmp_pp
{
#endif

#if 0
// general assignment from any Value
SnmpSyntax& TimeTicks::operator=(const SnmpSyntax&in_val)
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
        // case sNMP_SYNTAX_GAUGE32:    .. indistinquishable from UINT32
        case sNMP_SYNTAX_CNTR32:
        case sNMP_SYNTAX_TIMETICKS:
        case sNMP_SYNTAX_INT32: {       // implied cast int -> uint
            smival.value.uNumber =
                ((TimeTicks&)in_val).smival.value.uNumber;
            valid_flag = true;
            break;
        }
        }
    }
    m_changed = true;
    return *this;
}

#endif

// ASCII format return
const char* TimeTicks::get_printable() const
{
    if (m_changed == false)
    {
        return output_buffer;
    }

    TimeTicks* nc_this = PP_CONST_CAST(TimeTicks*, this);

    if (!valid_flag)
    {
        nc_this->output_buffer[0] = 0;
        nc_this->m_changed        = false;
        return output_buffer;
    }

    unsigned long hseconds = 0, seconds = 0, minutes = 0, hours = 0, days = 0;
    unsigned long tt = smival.value.uNumber;

    days = tt / 8640000;
    tt %= 8640000;

    hours = tt / 360000;
    tt %= 360000;

    minutes = tt / 6000;
    tt %= 6000;

    seconds = tt / 100;
    tt %= 100;

    hseconds = tt;

    if (days == 0)
    {
        snprintf(nc_this->output_buffer, sizeof(output_buffer),
            "%lu:%02lu:%02lu.%02lu", hours, minutes, seconds, hseconds);
    }
    else if (days == 1)
    {
        snprintf(nc_this->output_buffer, sizeof(output_buffer),
            "1 day %lu:%02lu:%02lu.%02lu", hours, minutes, seconds, hseconds);
    }
    else
    {
        snprintf(nc_this->output_buffer, sizeof(output_buffer),
            "%lu days, %lu:%02lu:%02lu.%02lu", days, hours, minutes, seconds,
            hseconds);
    }

    nc_this->m_changed = false;
    return output_buffer;
}

#ifdef SNMP_PP_NAMESPACE
} // end of namespace Snmp_pp
#endif
