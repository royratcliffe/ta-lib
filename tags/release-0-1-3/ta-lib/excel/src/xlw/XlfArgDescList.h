/*
 Copyright (C) 1998, 1999, 2001, 2002 J�r�me Lecomte

 This file is part of XLW, a free-software/open-source C++ wrapper of the
 Excel C API - http://xlw.sourceforge.net/

 XLW is free software: you can redistribute it and/or modify it under the
 terms of the XLW license.  You should have received a copy of the
 license along with this program; if not, please email xlw-users@lists.sf.net

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
*/

#ifndef INC_XlfArgDescList_H
#define INC_XlfArgDescList_H

/*!
\file XlfArgDescList.h
\brief Declares class XlfArgDescList.
*/

// $Id$

#include <xlw/XlfArgDesc.h>
#include <list>

#if defined(_MSC_VER)
#pragma once
#endif

//! Encapsulates argument list.
/*!
You can combine XlfArgDesc together with the operator+ and create XlfArgDescList
to be passed as argument to XlfFuncDesc::Register.

The operator=(), dtor, and the copy ctor are left generated by the compiler.
*/
class EXCEL32_API XlfArgDescList
{
public:
  //! Default ctor.
  XlfArgDescList();
  //! Copy ctor.
  XlfArgDescList(const XlfArgDescList& list);
  //! List initialization ctor.
  XlfArgDescList(const XlfArgDesc& first);
  //! Push a new argument in the list.
  XlfArgDescList& operator+(const XlfArgDesc& newarg);
  //! Type definition of the underlying container used to stored arguments.
  typedef std::list<XlfArgDesc> container_type;
  //! \ref STL
  typedef container_type::iterator iterator;
  //! \ref STL
  typedef container_type::const_iterator const_iterator;
  //! \ref STL
  iterator begin();
  //! \ref STL
  const_iterator begin() const;
  //! \ref STL
  iterator end();
  //! \ref STL
  const_iterator end() const;
  //! \ref STL
  size_t size() const;

  friend EXCEL32_API XlfArgDescList operator+(const XlfArgDesc&, const XlfArgDesc&);

private:
  //! Container of the arguments in the list.
  container_type arguments_;
};

//! Creates a list of argument from two XlfArgDesc.
EXCEL32_API XlfArgDescList operator+(const XlfArgDesc&, const XlfArgDesc&);

#endif