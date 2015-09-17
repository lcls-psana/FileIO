#ifndef FILEIO_STDFILEIO_H
#define FILEIO_STDFILEIO_H

//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id$
//
// Description:
//	Class FileIO
//
//------------------------------------------------------------------------

//-----------------
// C/C++ Headers --
//-----------------

//----------------------
// Base Class Headers --
//----------------------
#include "FileIO/FileIO_I.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

//		---------------------
// 		-- Class Interface --
//		---------------------


namespace FileIO {

  /**
   * implement calls to standard C library functions for file IO.
   */
class StdFileIO : public FileIO_I {

 public:
  // opening/closing
  virtual int open(const char *fname, int flags, mode_t mode = 0);
  virtual int open64 (const char *filename, int flags, mode_t mode = 0);
  virtual int close (int filedes);

  // reading/writing
  virtual ssize_t read(int filedes, void *buffer, size_t size);
  virtual ssize_t pread (int filedes, void *buffer, size_t size, off_t offset);
  virtual ssize_t pread64 (int filedes, void *buffer, size_t size, off64_t offset);
  virtual ssize_t write (int filedes, const void *buffer, size_t size);
  virtual ssize_t pwrite (int filedes, const void *buffer, size_t size, off_t offset);
  virtual ssize_t pwrite64 (int filedes, const void *buffer, size_t size, off64_t offset);
  
  // positioning
  virtual off_t lseek(int fileds, off_t offset, int whence);
  virtual off64_t lseek64 (int filedes, off64_t offset, int whence);

  //filesize
  virtual off_t filesize(int fileds);

}; // class StdFileIO

} // namespace FileIO

#endif  
