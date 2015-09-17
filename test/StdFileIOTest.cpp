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
#include "FileIO/StdFileIO.h"

using namespace FileIO;

#define BOOST_TEST_MODULE StdFileIO
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_1 )
{
  StdFileIO io;
  char tmpFname[128];
  strcpy(tmpFname, "tmpStdFileIO_XXXXXX");
  int fd = mkstemp(tmpFname);
  BOOST_CHECK_EQUAL( fd == -1, false);
  std::vector<uint8_t> buffer(10);
  for (int i =0; i < int(buffer.size()); ++i) buffer[i]=uint8_t(i);
  BOOST_CHECK_EQUAL(int(buffer.size()), io.write(fd, &buffer[0], buffer.size()));
  BOOST_CHECK_EQUAL(int(buffer.size()), io.filesize(fd));
  BOOST_CHECK_EQUAL(0,io.close(fd));
  fd = io.open(tmpFname, O_RDONLY);
  BOOST_CHECK_EQUAL( fd == -1, false);
  BOOST_CHECK_EQUAL( 5, io.lseek(fd, 5, SEEK_SET));
  BOOST_CHECK_EQUAL( 3, io.lseek(fd, -2, SEEK_CUR));
  BOOST_CHECK_EQUAL( 3, io.lseek(fd, 0, SEEK_CUR));
  std::vector<uint8_t> readbuffer(5);
  BOOST_CHECK_EQUAL( 5, io.read(fd, &readbuffer[0], 5));
  for (int i=0; i < int(readbuffer.size()); ++i) {
    BOOST_CHECK_EQUAL(readbuffer[i], 3+i);
  }
  BOOST_CHECK_EQUAL(0,io.close(fd));
  unlink(tmpFname);
}
