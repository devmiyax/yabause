#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class MacwTest : public ::testing::Test {
 protected:
   SH2Interface_struct* pctx_;

  MacwTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~MacwTest() {   
  }   

virtual void SetUp() {
 
  
}

virtual void TearDown() {


}

};

TEST_F(MacwTest, normal) {

  MSH2->regs.R[15]=0x06000fc0;
  MSH2->regs.MACH =(0xffffff1b);
  MSH2->regs.MACL =(0xffff23fe);

  MappedMemoryWriteWord( 0x06000fc0, 0xff3b );
  MappedMemoryWriteWord( 0x06000fc2, 0x00ac );

  // mac.l @r7+, @r6+
  MappedMemoryWriteWord( 0x06000000, 0x4fff );
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop

  MSH2->regs.PC =( 0x06000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0xffffff1b, MSH2->regs.MACH );
  EXPECT_EQ( 0xfffe9fa2, MSH2->regs.MACL );

}

TEST_F(MacwTest, s) {

  MSH2->regs.R[15]=0x06000fc0;
  MSH2->regs.MACH =(0xffffff1b);
  MSH2->regs.MACL =(0xffff23fe);
  MSH2->regs.SR.all =(0x00000002);

  MappedMemoryWriteWord( 0x06000fc0, 0xff3b );
  MappedMemoryWriteWord( 0x06000fc2, 0x00ac );

  // mac.l @r7+, @r6+
  MappedMemoryWriteWord( 0x06000000, 0x4fff );
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop

  MSH2->regs.PC =( 0x06000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0xffffff1b, MSH2->regs.MACH );
  EXPECT_EQ( 0xfffe9fa2, MSH2->regs.MACL );

}


}  // namespace
