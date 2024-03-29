/*_############################################################################
 * _##
 * _##  integer.h
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
 * SNMP++ I N T E G E R. H
 *
 * INTEGER CLASS DEFINITION
 *
 * DESIGN + AUTHOR:  Jeff Meyer
 *
 * DESCRIPTION:
 * Class definition for Integer classes.
 *
 * =====================================================================*/

#ifndef _SNMP_INTEGER_H_
#define _SNMP_INTEGER_H_

#include "snmp_pp/smival.h"

#include <libsnmp.h>

#ifdef SNMP_PP_NAMESPACE
namespace Snmp_pp
{
#endif

#define INTOUTBUF 15 // largest ASCII formatted integer

//------------[ Integer Classes ]------------------------------------------

/**
 * 32 bit unsigned integer class.
 *
 * The integer class allows all the functionality of the various
 * integers but is contained in a Value object for consistency
 * among the various types.
 * class objects may be set or get into Vb objects.
 */
class DLLOPT SnmpUInt32 : public SnmpSyntax {
public:
    /**
     * Constructor with value (defaults to 0).
     *
     * @param i - initial value
     */
    SnmpUInt32(const uint32_t i = 0)
        : SnmpSyntax(), valid_flag(true), m_changed(true)
    {
        smival.value.uNumber = i;
        smival.syntax        = sNMP_SYNTAX_UINT32;
    }

    /**
     * Copy constructor.
     *
     * @param c - initial value
     */
    SnmpUInt32(const SnmpUInt32& c)
        : SnmpSyntax(), valid_flag(c.valid_flag), m_changed(true)
    {
        smival.value.uNumber = c.smival.value.uNumber;
        smival.syntax        = sNMP_SYNTAX_UINT32;
    }

    /**
     * Destructor (ensure that SnmpSyntax::~SnmpSyntax() is overridden).
     */
    ~SnmpUInt32() override { }

    /**
     * Return the syntax.
     *
     * @return This method always returns sNMP_SYNTAX_UINT32.
     */
    SmiUINT32 get_syntax() const override { return sNMP_SYNTAX_UINT32; }

    /**
     * Overloaded assignment for unsigned longs.
     *
     * @param i - new value
     * @return self reference
     */
    SnmpUInt32& operator=(const uint32_t i)
    {
        smival.value.uNumber = i;
        valid_flag           = true;
        m_changed            = true;
        return *this;
    }

    /**
     * Overloaded assignment for SnmpUInt32.
     *
     * @param uli - new value
     * @return self reference
     */
    SnmpUInt32& operator=(const SnmpUInt32& uli)
    {
        if (this == &uli)
        {
            return *this; // check for self assignment
        }
        smival.value.uNumber = uli.smival.value.uNumber;
        valid_flag           = uli.valid_flag;
        m_changed            = true;
        return *this;
    }

    /**
     * Map other SnmpSyntax objects to SnmpUInt32.
     */
    SnmpSyntax& operator=(const SnmpSyntax& val) override;

    /**
     * Behave like an uint32_t.
     *
     * @return value as uint32_t
     */
    operator uint32_t() const { return smival.value.uNumber; }

    /**
     * Get a printable ASCII value.
     */
    [[nodiscard]] const char* get_printable() const override;

    /**
     * Clone operator.
     *
     * @return Pointer to a newly created copy of the object.
     */
    [[nodiscard]] SnmpSyntax* clone() const override
    {
        return (SnmpSyntax*)new SnmpUInt32(*this);
    }

    /**
     * Return validity of the object.
     * An SnmpUInt32 will only be invalid after a failed asignment
     * of another SnmpSyntax object.
     */
    bool valid() const override { return valid_flag; }

    /**
     * Return the space needed for serialization.
     */
    int get_asn1_length() const override;

    /**
     * Reset the object.
     */
    void clear() override
    {
        smival.value.uNumber = 0;
        valid_flag           = true;
        m_changed            = true;
    }

protected:
    bool                 valid_flag;
    SNMP_PP_MUTABLE char output_buffer[INTOUTBUF] {};
    SNMP_PP_MUTABLE bool m_changed;
};

/**
 * 32 bit signed integer class.
 */
class DLLOPT SnmpInt32 : public SnmpSyntax {
public:
    /**
     * Constructor with value.
     *
     * @param i - initial value
     */
    SnmpInt32(const int32_t i = 0)
        : SnmpSyntax(), valid_flag(true), m_changed(true)
    {
        smival.value.sNumber = i;
        smival.syntax        = sNMP_SYNTAX_INT32;
    }

    /**
     * Copy constructor.
     *
     * @param c - initial value
     */
    SnmpInt32(const SnmpInt32& c)
        : SnmpSyntax(), valid_flag(c.valid_flag), m_changed(true)
    {
        smival.value.sNumber = c.smival.value.sNumber;
        smival.syntax        = sNMP_SYNTAX_INT32;
    }

    /**
     * Destructor (ensure that SnmpSyntax::~SnmpSyntax() is overridden).
     */
    ~SnmpInt32() override { }

    /**
     * Return the syntax.
     *
     * @return This method always returns sNMP_SYNTAX_INT32.
     */
    SmiUINT32 get_syntax() const override { return sNMP_SYNTAX_INT32; }

    /**
     * Overloaded assignment for longs.
     *
     * @param i - new value
     * @return self reference
     */
    SnmpInt32& operator=(const int32_t i)
    {
        smival.value.sNumber = i;
        valid_flag           = true;
        m_changed            = true;
        return *this;
    }

    /**
     * Overloaded assignment for SnmpInt32.
     *
     * @param li - new value
     * @return self reference
     */
    SnmpInt32& operator=(const SnmpInt32& li)
    {
        if (this == &li)
        {
            return *this; // check for self assignment
        }
        smival.value.sNumber = li.smival.value.sNumber;
        valid_flag           = li.valid_flag;
        m_changed            = true;
        return *this;
    }

    /**
     * Map other SnmpSyntax objects to SnmpInt32.
     */
    SnmpSyntax& operator=(const SnmpSyntax& val) override;

    /**
     * Behave like an long.
     *
     * @return value as long
     */
    operator int32_t() const { return (int32_t)smival.value.sNumber; }

    /**
     * Get a printable ASCII value.
     */
    [[nodiscard]] const char* get_printable() const override;

    /**
     * Clone operator.
     *
     * @return Pointer to a newly created copy of the object.
     */
    [[nodiscard]] SnmpSyntax* clone() const override
    {
        return (SnmpSyntax*)new SnmpInt32(*this);
    }

    /**
     * Return validity of the object.
     * An SnmpUInt32 will only be invalid after a failed asignment
     * of another SnmpSyntax object.
     */
    bool valid() const override { return valid_flag; }

    /**
     * Return the space needed for serialization.
     */
    int get_asn1_length() const override;

    /**
     * Reset the object.
     */
    void clear() override
    {
        smival.value.sNumber = 0;
        valid_flag           = true;
        m_changed            = true;
    }

protected:
    bool                 valid_flag;
    SNMP_PP_MUTABLE char output_buffer[INTOUTBUF] {};
    SNMP_PP_MUTABLE bool m_changed;
};

#ifdef SNMP_PP_NAMESPACE
} // end of namespace Snmp_pp
#endif

#endif // _SNMP_INTEGER_H_
