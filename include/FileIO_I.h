#ifndef FILEIO_FILEIO_I_H
#define FILEIO_FILEIO_I_H

//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id$
//
// Description:
//	Class FileIO_I
//
//------------------------------------------------------------------------

//-----------------
// C/C++ Headers --
//-----------------
#include <fcntl.h>
#include <unistd.h>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

//		---------------------
// 		-- Class Interface --
//		---------------------


namespace FileIO {

  /**
   * interface to fileIO. Currently provides low level file descriptor based 
   * file IO and higher level function filesize
   */
class FileIO_I {

 public:
  virtual ~FileIO_I() {};
  // opening/closing
  virtual int open(const char *fname, int flags, mode_t mode = 0);
  virtual int open64(const char *filename, int flags, mode_t mode = 0);
  virtual int close(int filedes);

  // reading/writing
  virtual ssize_t read(int filedes, void *buffer, size_t size);
  virtual ssize_t pread(int filedes, void *buffer, size_t size, off_t offset);
  virtual ssize_t pread64(int filedes, void *buffer, size_t size, off64_t offset);
  virtual ssize_t write(int filedes, const void *buffer, size_t size);
  virtual ssize_t pwrite(int filedes, const void *buffer, size_t size, off_t offset);
  virtual ssize_t pwrite64(int filedes, const void *buffer, size_t size, off64_t offset);
  
  // positioning
  virtual off_t lseek(int fileds, off_t offset, int whence);
  virtual off64_t lseek64(int filedes, off64_t offset, int whence);

  //filesize
  virtual off_t filesize(int fileds);

}; // class FileIO_I

} // namespace FileIO

#endif  
