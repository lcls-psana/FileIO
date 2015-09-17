//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id$
//
// Description:
//	Class Exceptions...
//
// Author List:
//
//------------------------------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "FileIO/Exceptions.h"

//-----------------
// C/C++ Headers --
//-----------------

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

//-----------------------------------------------------------------------
// Local Macros, Typedefs, Structures, Unions and Forward Declarations --
//-----------------------------------------------------------------------

//		----------------------------------------
// 		-- Public Function Member Definitions --
//		----------------------------------------

namespace FileIO {

//----------------
// Constructors --
//----------------
Exception::Exception (const ErrSvc::Context& ctx, const std::string& className, const std::string& what)
  : ErrSvc::Issue(ctx, className+": "+what)
{
}

} // namespace FileIO
