//--------------------------------------------------------------------------
// File and Version Information:
// 	$Id$
//
// Description:
//	Test suite case for StdFileIOTest
//
//------------------------------------------------------------------------

//---------------
// C++ Headers --
//---------------
#include <stdio.h>
#include <sys/stat.h>

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "FileIO/MockFileIO.h"
#include "FileIO/Exceptions.h"

using namespace FileIO;

#define BOOST_TEST_MODULE MockFileIO
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_1 )
{
  std::string fname("myfile");
  MockFileIO::MapOff2Buffer off2buffer;
  std::vector<uint8_t> buffer(10);
  for (int i =0; i < int(buffer.size()); ++i) buffer[i]=uint8_t(i);
  off2buffer[0]=buffer;
  for (int i =0; i < int(buffer.size()); ++i) buffer[i] += 100;
  off2buffer[20]=buffer;

  MockFileIO::MapFname2Off2Buffer fname2offs;
  fname2offs[fname]=off2buffer;
  MockFileIO io(fname2offs);

  // can't open files not in the map we initialized MockFileIO with:
  BOOST_CHECK_EQUAL(-1, io.open("otherfile", O_RDONLY));

  int fd = io.open(fname.c_str(), O_RDONLY);
  BOOST_CHECK_EQUAL(1,fd);
  
  // can't open the same file more then once with MockIO
  BOOST_CHECK_THROW(io.open(fname.c_str(), O_RDONLY), MockException);

  // can read from offsets in map
  std::vector<uint8_t> rbuffer(10);
  BOOST_CHECK_EQUAL(10, io.read(fd, &rbuffer.at(0), 10));
  for (int i = 0; i < 10; ++i) BOOST_CHECK_EQUAL(i, rbuffer[i]);

  BOOST_CHECK_EQUAL(20, io.lseek(fd, 20, SEEK_SET));
  BOOST_CHECK_EQUAL(10, io.read(fd, &rbuffer.at(0), 10));
  for (int i = 0; i < 10; ++i) BOOST_CHECK_EQUAL(100+i, rbuffer[i]);

  // if ask to read more than what was stored at an offset, just get what is there:
  BOOST_CHECK_EQUAL(20, io.lseek(fd, 20, SEEK_SET));
  rbuffer.resize(999);
  BOOST_CHECK_EQUAL(10, io.read(fd, &rbuffer.at(0), 999));

  // file position is updated correctly
  BOOST_CHECK_EQUAL(30, io.lseek(fd, 0, SEEK_CUR));

  // try to read from offset other than what is in map, exception
  BOOST_CHECK_EQUAL(5, io.lseek(fd, 5, SEEK_SET));
  BOOST_CHECK_EQUAL(5, io.lseek(fd, 0, SEEK_CUR));
  BOOST_CHECK_THROW(io.read(fd, &rbuffer.at(0), 3), MockException);
  BOOST_CHECK_EQUAL(5, io.lseek(fd, 0, SEEK_CUR));

  BOOST_CHECK_EQUAL(30, io.filesize(fd));

  BOOST_CHECK_EQUAL(0, io.close(fd));

  // can't close file twice
  BOOST_CHECK_EQUAL(-1, io.close(fd));

  // operations don't work on closed file
  BOOST_CHECK_EQUAL(-1, io.filesize(fd));
  BOOST_CHECK_EQUAL(-1, io.lseek(fd, 10, SEEK_SET));
  BOOST_CHECK_EQUAL(-1, io.read(fd, &rbuffer.at(0), 3));

  // but we can re-open file
  fd = io.open(fname.c_str(), O_RDONLY);
  BOOST_CHECK_EQUAL(1,fd);

  // and things will work
  BOOST_CHECK_EQUAL(30, io.filesize(fd));
  BOOST_CHECK_EQUAL(20, io.lseek(fd, 20, SEEK_SET));
  BOOST_CHECK_EQUAL(3, io.read(fd, &rbuffer.at(0), 3));
  BOOST_CHECK_EQUAL(23, io.lseek(fd,0,SEEK_CUR));
}
