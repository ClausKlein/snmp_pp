/*_############################################################################
 * _##
 * _##  gauge.h
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
 * purpose. It is provided "AS-IS without warranty of any kind,either express
 * or implied. User hereby grants a royalty-free license to any and all
 * derivatives based upon this software code base.
 *
 *
 * SNMP++ G A U G E. H
 *
 * GAUGE32 CLASS DEFINITION
 *
 * DESIGN + AUTHOR:  Peter E Mellquist
 *
 * DESCRIPTION:
 * Class definition for SMI Gauge32 class.
 * =====================================================================*/

#ifndef _SNMP_GAUGE_H_
#define _SNMP_GAUGE_H_

#include "snmp_pp/integer.h"

#ifdef SNMP_PP_NAMESPACE
namespace Snmp_pp
{
#endif

//------------[ Gauge32 Class ]------------------------------------------

/**
 * The gauge class allows all the functionality of unsigned integers
 * but is recognized as a distinct SMI type. Gauge32 objects may be
 * set or get into Vb objects.
 */
class DLLOPT Gauge32 : public SnmpUInt32 {
public:
    //-----------[ Constructors and Destrucotr ]----------------------

    /**
     * Constructs a valid Gauge32 with the given value.
     *
     * @param ul - value (0..MAX_UINT32)
     */
    Gauge32(const uint32_t ul = 0) : SnmpUInt32(ul)
    {
        smival.syntax = sNMP_SYNTAX_GAUGE32;
    }

    /**
     * Copy constructor.
     *
     * @param g32 - value
     */
    Gauge32(const Gauge32& g32) : SnmpUInt32(g32)
    {
        smival.syntax = sNMP_SYNTAX_GAUGE32;
    }

    /**
     * Destructor (ensure that SnmpUInt32::~SnmpUInt32() is overridden).
     */
    ~Gauge32() override { }

    //-----------[ SnmpSyntax methods ]----------------------

    /**
     * Get the Syntax of the object.
     *
     * @return This method always returns sNMP_SYNTAX_GAUGE32.
     */
    SmiUINT32 get_syntax() const override { return sNMP_SYNTAX_GAUGE32; }

    /**
     * Clone the object.
     *
     * @return A cloned Gauge32 object allocated through new.
     */
    [[nodiscard]] SnmpSyntax* clone() const override
    {
        return (SnmpSyntax*)new Gauge32(*this);
    }

    //-----------[ Overload some operators ]----------------------

    using SnmpUInt32::operator=;

    /**
     * Assign a Gauge32 to a Gauge32.
     */
    Gauge32& operator=(const Gauge32& uli)
    {
        smival.value.uNumber = uli.smival.value.uNumber;
        valid_flag           = uli.valid_flag;
        m_changed            = true;
        return *this;
    }

    /**
     * Assign a uint32_t to a Gauge32.
     *
     * @param ul - New value
     */
    Gauge32& operator=(const uint32_t ul)
    {
        SnmpUInt32::operator=(ul);

        return *this;
    }
};

#ifdef SNMP_PP_NAMESPACE
} // end of namespace Snmp_pp
#endif

#endif // _SNMP_GAUGE_H_
