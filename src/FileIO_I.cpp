//--------------------------------------------------------------------------
// File and Version Information:
//     $Id$
//
// Description:
//     Class FileIO_I
//
// Author List:
//
//------------------------------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "FileIO/FileIO_I.h"

//-----------------
// C/C++ Headers --
//-----------------

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "FileIO/Exceptions.h"

//-----------------------------------------------------------------------
// Local Macros, Typedefs, Structures, Unions and Forward Declarations --
//-----------------------------------------------------------------------


//              ----------------------------------------
//              -- Public Function Member Definitions --
//              ----------------------------------------

namespace FileIO {

  // opening/closing
  int FileIO_I::open(const char *fname, int flags, mode_t mode) {
    throw NotImplementedException(ERR_LOC,"open" );
  }

  int FileIO_I::open64 (const char *filename, int flags, mode_t mode) {
    throw NotImplementedException(ERR_LOC,"open64" );
  }

  int FileIO_I::close (int filedes) {
    throw NotImplementedException(ERR_LOC,"close" );
  }


  // reading/writing
  ssize_t FileIO_I::read(int filedes, void *buffer, size_t size) {
    throw NotImplementedException(ERR_LOC,"read" );
  }

  ssize_t FileIO_I::pread (int filedes, void *buffer, size_t size, off_t offset) {
    throw NotImplementedException(ERR_LOC,"pread" );
  }

  ssize_t FileIO_I::pread64 (int filedes, void *buffer, size_t size, off64_t offset) {
    throw NotImplementedException(ERR_LOC,"pread64" );
  }

  ssize_t FileIO_I::write (int filedes, const void *buffer, size_t size) {
    throw NotImplementedException(ERR_LOC,"write" );
  }

  ssize_t FileIO_I::pwrite (int filedes, const void *buffer, size_t size, off_t offset) {
    throw NotImplementedException(ERR_LOC,"pwrite" );
  }

  ssize_t FileIO_I::pwrite64 (int filedes, const void *buffer, size_t size, off64_t offset) {
    throw NotImplementedException(ERR_LOC,"pwrite64" );
  }

  
  // positioning
  off_t FileIO_I::lseek(int fileds, off_t offset, int whence) {
    throw NotImplementedException(ERR_LOC,"lseek" );
  }

  off64_t FileIO_I::lseek64 (int filedes, off64_t offset, int whence) {
    throw NotImplementedException(ERR_LOC,"lseek64" );
  }

  // filesize
  off_t FileIO_I::filesize(int filedes) {
    throw NotImplementedException(ERR_LOC,"filesize" );
  }
}; // namespace FileIO

