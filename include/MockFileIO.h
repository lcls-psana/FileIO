#ifndef FILEIO_MOCKFILEIO_H
#define FILEIO_MOCKFILEIO_H

//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id$
//
// Description:
//	Class MockFileIO
//
//------------------------------------------------------------------------

//-----------------
// C/C++ Headers --
//-----------------
#include <map>
#include <vector>
#include <string>

#include <stdint.h>

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
   * MockFileIO implements some of the FileIO functions for
   * mock testing.
   *
   * For testing applications that will only open the same file
   * once, and will read from specific positions that you want
   * to test. That is read throws an Exception if the client
   * reads from different positions in the file other than
   * how MockFileIO is initialized.
   *
   * @usage
   * Create a list of offsets for some filenames along with buffers of
   * bytes to read back at those offsets.
   *
   * initalize MockFileIO with this data.
   *
   * implements open, close, lseek, read and filesize - based on
   * initialization data.
   *
   * See unit test in tests/ directory for example.
   * 
   */
class MockFileIO : public FileIO_I {

public:

  typedef std::map<off_t, std::vector<uint8_t> > MapOff2Buffer;
  typedef std::map<std::string, MapOff2Buffer> MapFname2Off2Buffer;

  MockFileIO(const MapFname2Off2Buffer & mapFname2Off2Buffer);

  virtual int open(const char *fname, int flags, mode_t mode = 0);
  virtual int close (int filedes);
  virtual off_t lseek(int fileds, off_t offset, int whence);
  virtual ssize_t read(int filedes, void *buffer, size_t size);
  virtual off_t filesize(int fileds);
  
 private:
  const MapFname2Off2Buffer &m_fname2off2buffer;
  struct FileInfo {
    int fd; off_t pos; bool open;
    FileInfo() :fd(-1), pos(0), open(false) {}; 
    FileInfo(int _fd, off_t _pos, bool _open) 
    : fd(_fd), pos(_pos), open(_open) {};
  };
  typedef std::map<std::string, FileInfo> MapFiles;  
  MapFiles m_fileInfo;

  ssize_t readFromMap(const std::string &fname, void *buffer, size_t size, off_t pos);

  FileInfo * getFileInfo(int fd, std::string &fname);

}; // class MockFileIO


} // namespace FileIO

#endif  
