#ifndef FILEIO_EXCEPTIONS_H
#define FILEIO_EXCEPTIONS_H

//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id: Exceptions.h 10654 2015-09-09 20:14:49Z davidsch@SLAC.STANFORD.EDU $
//
// Description:
//	Class Exceptions.
//
//------------------------------------------------------------------------

//-----------------
// C/C++ Headers --
//-----------------

//----------------------
// Base Class Headers --
//----------------------
#include "ErrSvc/Issue.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

//------------------------------------
// Collaborating Class Declarations --
//------------------------------------

//		---------------------
// 		-- Class Interface --
//		---------------------

namespace FileIO {

/// @addtogroup FileIO

/**
 *  @ingroup FileIO
 *
 *  @brief Exception classes
 *
 *  This software was developed for the LUSI project.  If you use all or
 *  part of it, please give an appropriate acknowledgement.
 *
 *  @version $Id$
 *
 *  @author
 */

class Exception : public ErrSvc::Issue {
public:
  // Constructor
  Exception(const ErrSvc::Context& ctx, const std::string& className, const std::string& what);
};

class NotImplementedException : public Exception {
public:
  // Constructor
 NotImplementedException(const ErrSvc::Context& ctx, const std::string& function) :
  Exception(ctx, "NotImplemented", function) {}
};

class MockException : public Exception {
public:
  // Constructor
 MockException(const ErrSvc::Context& ctx, const std::string& msg) :
  Exception(ctx, "MockException", msg) {}
};


} // namespace FileIO

#endif // FILEIO_EXCEPTIONS_H
