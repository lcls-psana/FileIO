//--------------------------------------------------------------------------
// File and Version Information:
//     $Id$
//
// Description:
//     Class StdFileIO
//
// Author List:
//
//------------------------------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "FileIO/StdFileIO.h"

//-----------------
// C/C++ Headers --
//-----------------
#include <sys/stat.h>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

//-----------------------------------------------------------------------
// Local Macros, Typedefs, Structures, Unions and Forward Declarations --
//-----------------------------------------------------------------------


//              ----------------------------------------
//              -- Public Function Member Definitions --
//              ----------------------------------------

namespace FileIO {

  // opening/closing
  int StdFileIO::open(const char *fname, int flags, mode_t mode) {
   return ::open(fname, flags, mode);
  }

  int StdFileIO::open64 (const char *filename, int flags, mode_t mode) {
   return ::open64(filename, flags, mode);
  }

  int StdFileIO::close (int filedes) {
   return ::close(filedes);
  }


  // reading/writing
  ssize_t StdFileIO::read(int filedes, void *buffer, size_t size) {
   return ::read(filedes, buffer, size);
  }

  ssize_t StdFileIO::pread (int filedes, void *buffer, size_t size, off_t offset) {
   return ::pread(filedes, buffer, size, offset);
  }

  ssize_t StdFileIO::pread64 (int filedes, void *buffer, size_t size, off64_t offset) {
   return ::pread64(filedes, buffer, size, offset);
  }

  ssize_t StdFileIO::write (int filedes, const void *buffer, size_t size) {
   return ::write(filedes, buffer, size);
  }

  ssize_t StdFileIO::pwrite (int filedes, const void *buffer, size_t size, off_t offset) {
   return ::pwrite(filedes, buffer, size, offset);
  }

  ssize_t StdFileIO::pwrite64 (int filedes, const void *buffer, size_t size, off64_t offset) {
   return ::pwrite64(filedes, buffer, size, offset);
  }

  
  // positioning
  off_t StdFileIO::lseek(int fileds, off_t offset, int whence) {
   return ::lseek(fileds, offset, whence);
  }

  off64_t StdFileIO::lseek64 (int filedes, off64_t offset, int whence) {
   return ::lseek64(filedes, offset, whence);
  }

  // filesize
  off_t StdFileIO::filesize(int fileds) {
    struct stat statResults;
    if (0 != fstat(fileds, &statResults)) return -1;
    return statResults.st_size;
  }


}; // namespace FileIO

