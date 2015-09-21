//--------------------------------------------------------------------------
// File and Version Information:
//     $Id$
//
// Description:
//     Class MockFileIO
//
// Author List:
//
//------------------------------------------------------------------------

//-----------------------
// This Class's Header --
//-----------------------
#include "FileIO/MockFileIO.h"

//-----------------
// C/C++ Headers --
//-----------------
#include <algorithm>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "MsgLogger/MsgLogger.h"
#include "FileIO/Exceptions.h"

//-----------------------------------------------------------------------
// Local Macros, Typedefs, Structures, Unions and Forward Declarations --
//-----------------------------------------------------------------------

namespace {
  std::string jnk;
  const char *logger = "MockFileIO";
}

//              ----------------------------------------
//              -- Public Function Member Definitions --
//              ----------------------------------------

namespace FileIO {

MockFileIO::MockFileIO(const MapFname2Off2Buffer & mapFname2Off2Buffer) :
  m_fname2off2buffer(mapFname2Off2Buffer)
{
  updateFileInfo();
}

void MockFileIO::updateFileInfo() {
  int nextFd = 0;
  for (MapFiles::iterator it = m_fileInfo.begin();
       it != m_fileInfo.end(); ++it) {
    nextFd = std::max(nextFd, it->second.fd);
  }
  ++nextFd;
  for (MapFname2Off2Buffer::const_iterator it = m_fname2off2buffer.begin();
       it != m_fname2off2buffer.end(); ++it) {
    if (m_fileInfo.find(it->first) == m_fileInfo.end()) {
      m_fileInfo[it->first]=FileInfo(nextFd, 0, false);
      ++nextFd;
    }
  }
}

// opening/closing
int MockFileIO::open(const char *fname, int flags, mode_t mode) {
  updateFileInfo();
  MapFiles::iterator pos = m_fileInfo.find(std::string(fname));
  if (pos == m_fileInfo.end()) return -1;
  FileInfo &fi = pos->second;
  if (fi.open) throw MockException(ERR_LOC, "file already opened. Multiple opens not supported");
  fi.open = true;
  fi.pos = 0;
  return fi.fd;
}
  
int MockFileIO::close(int filedes) {
  FileInfo *fi = getFileInfo(filedes, jnk);
  if (fi==NULL or (not fi->open)) return -1;
  fi->open = false;
  fi->pos = 0;
  return 0;
}

// reading/writing
ssize_t MockFileIO::read(int filedes, void *buffer, size_t size) {
  std::string fname;
  FileInfo *fi = getFileInfo(filedes, fname);
  if (fi == NULL or (not fi->open)) return -1;
  ssize_t nread = readFromMap(fname, buffer, size, fi->pos);
  fi->pos += nread;
  return nread;
}

ssize_t MockFileIO::readFromMap(const std::string &fname, void *buffer, size_t size, off_t pos) {
  MapFname2Off2Buffer::const_iterator cit = m_fname2off2buffer.find(fname);
  if (cit == m_fname2off2buffer.end()) throw MockException(ERR_LOC, "");
  const MapOff2Buffer & mapOff2Buffer = cit->second;
  MapOff2Buffer::const_iterator cjt = mapOff2Buffer.find(pos);
  if (cjt == mapOff2Buffer.end()) {
    MsgLog(logger, error, "readFromMap - bad offset. fname=" << fname << " offset=" << pos);
    throw MockException(ERR_LOC, "Bad Offset");
  }
  const std::vector<uint8_t> &fileBuffer = cjt->second;
  uint8_t *p = (uint8_t*)buffer;
  size_t bytesCopied = 0;
  while ((bytesCopied < size) and (bytesCopied < fileBuffer.size())) {
    *p++ = fileBuffer[bytesCopied++];
  }
  MsgLog(logger, debug, "readFromMap. Read " << bytesCopied << " from offset=" << pos << " fname=" << fname);
  return bytesCopied;
}

off_t MockFileIO::lseek(int fileds, off_t offset, int whence) {
  FileInfo *fi = getFileInfo(fileds, jnk);
  if ((fi==NULL) or (not fi->open)) {
    MsgLog(logger, debug, "lseek(fd="  << fileds <<",offset="<<offset<<",whence="<<whence<<")"<< " return -1");
    return -1;
  }
  off_t newPos = 0;
  if (whence == SEEK_CUR) {
    newPos = fi->pos += offset;
  } else if (whence == SEEK_SET) {
    newPos = offset;
  } else {
    MsgLog(logger, error, "whence=" << whence << " in constrast to SEEK_CUR=" << SEEK_CUR 
           << " and SEEK_SET=" << SEEK_SET);
    throw MockException(ERR_LOC, "lseek doesn't handle whence");
  }
  if (newPos < 0) {
    MsgLog(logger, debug, "lseek(fd="  << fileds <<",offset="<<offset<<",whence="<<whence<<")"<< " newPos < 0 so return -1");
    return -1;
  }
  fi->pos = newPos;
  MsgLog(logger, debug, "lseek(fd="  << fileds <<",offset="<<offset<<",whence="<<whence<<")"<< " return " << newPos);
  return newPos;
}

off_t MockFileIO::filesize(int fileds) {
  std::string fname;
  FileInfo *fi = getFileInfo(fileds, fname);
  if (fi==NULL or (not fi->open)) return -1;
  MapFname2Off2Buffer::const_iterator it = m_fname2off2buffer.find(fname);
  if (it == m_fname2off2buffer.end()) return -1;
  const MapOff2Buffer & mapOff2Buffer = it->second;
  off_t sz = 0;
  for (MapOff2Buffer::const_iterator jt = mapOff2Buffer.begin(); 
       jt != mapOff2Buffer.end(); ++jt) {
    off_t candSz = jt->first + jt->second.size();
    sz = std::max(sz, candSz);
  }
  return sz;
}

MockFileIO::FileInfo * MockFileIO::getFileInfo(int fd, std::string &fname) {
  for (MapFiles::iterator pos = m_fileInfo.begin(); pos != m_fileInfo.end(); ++pos) {
    FileInfo &fi = pos->second;
    if (fi.fd == fd) {
      fname = pos->first;
      return &fi;
    }
  }
  return NULL;
}

std::ostream & MockFileIO::dump(std::ostream &o) const {
  for (MapFname2Off2Buffer::const_iterator it = m_fname2off2buffer.begin();
       it != m_fname2off2buffer.end(); ++it) {
    o << it->first << std::endl;
    for (MapOff2Buffer::const_iterator jt = it->second.begin();
         jt != it->second.end(); ++jt) {
      o << "   offset=" << jt->first << "  buflen=" << jt->second.size() << std::endl;
    }
  }
  return o;
}

}; // namespace FileIO

