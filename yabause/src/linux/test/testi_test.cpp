#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class TestiTest : public ::testing::Test {
 protected:
   SH2Interface_struct* pctx_;

  TestiTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~TestiTest() {    
  }

virtual void SetUp() {
 
}

virtual void TearDown() {
}

};

TEST_F(TestiTest, normal) {

  MSH2->regs.R[0]=0x000000FA;

  // tst R[0]x, 0xFA
  MappedMemoryWriteWord( 0x06000000, 0xC8FA );
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop

  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x00, (MSH2->regs.SR.all&0x01) );
  EXPECT_EQ( 0x000000FA, MSH2->regs.R[0]);
}



TEST_F(TestiTest, normal2) {

  MSH2->regs.R[0]=0x0000000F;

 // tst R[0]x, 0xF0
  MappedMemoryWriteWord( 0x06000000, 0xC8F0 );
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop
  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x01, (MSH2->regs.SR.all&0x01) );

}

}  // namespace
