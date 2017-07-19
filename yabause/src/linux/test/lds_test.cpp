#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class LdsTest : public ::testing::Test {
 protected:
   SH2Interface_struct* pctx_;

  LdsTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~LdsTest() { 
  }   

virtual void SetUp() {
  
}

virtual void TearDown() {

}

};

TEST_F(LdsTest, ldsmach) {

  MSH2->regs.R[1]=0x03216721;

  MappedMemoryWriteWord( 0x06000000, 0x410A );
  MappedMemoryWriteWord( 0x06000002, 0x000b );
  MappedMemoryWriteWord( 0x06000004, 0x0009 );
  MappedMemoryWriteLong( 0x06000250, 0x03216721 );

  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x00000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x03216721, MSH2->regs.R[1] );
  EXPECT_EQ( 0x03216721, MSH2->regs.MACH );
}

TEST_F(LdsTest, ldsmmach) {

  MSH2->regs.R[1]=0x06000250;

  MappedMemoryWriteWord( 0x06000000, 0x4106 );
  MappedMemoryWriteWord( 0x06000002, 0x000b );
  MappedMemoryWriteWord( 0x06000004, 0x0009 );
  MappedMemoryWriteLong( 0x06000250, 0x03216721 );

  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x00000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x06000254, MSH2->regs.R[1] );
  EXPECT_EQ( 0x03216721, MSH2->regs.MACH );
}

TEST_F(LdsTest, ldsmacl) {

  MSH2->regs.R[1]=0x03216721;

  MappedMemoryWriteWord( 0x06000000, 0x411A );
  MappedMemoryWriteWord( 0x06000002, 0x000b );
  MappedMemoryWriteWord( 0x06000004, 0x0009 );
  MappedMemoryWriteLong( 0x06000250, 0x03216721 );

  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x00000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x03216721, MSH2->regs.R[1] );
  EXPECT_EQ( 0x03216721, MSH2->regs.MACL );
}

TEST_F(LdsTest, ldsmmacl) {

  MSH2->regs.R[1]=0x06000250;

  MappedMemoryWriteWord( 0x06000000, 0x4116 );
  MappedMemoryWriteWord( 0x06000002, 0x000b );
  MappedMemoryWriteWord( 0x06000004, 0x0009 );
  MappedMemoryWriteLong( 0x06000250, 0x03216721 );

  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x00000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x06000254, MSH2->regs.R[1] );
  EXPECT_EQ( 0x03216721, MSH2->regs.MACL );
}

TEST_F(LdsTest, ldspr) {

  MSH2->regs.R[1]=0x03216721;

  MappedMemoryWriteWord( 0x06000000, 0x412A );
  MappedMemoryWriteWord( 0x06000002, 0x000b );
  MappedMemoryWriteWord( 0x06000004, 0x0009 );
  MappedMemoryWriteLong( 0x06000250, 0x03216721 );

  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x00000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x03216721, MSH2->regs.R[1] );
  EXPECT_EQ( 0x03216721, MSH2->regs.PR );
}

TEST_F(LdsTest, ldsmpr) {

  MSH2->regs.R[1]=0x06000250;

  MappedMemoryWriteWord( 0x06000000, 0x4126 );
  MappedMemoryWriteWord( 0x06000002, 0x000b );
  MappedMemoryWriteWord( 0x06000004, 0x0009 );
  MappedMemoryWriteLong( 0x06000250, 0x03216721 );

  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x00000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x06000254, MSH2->regs.R[1] );
  EXPECT_EQ( 0x03216721, MSH2->regs.PR );
}

}  // namespacegPtr
