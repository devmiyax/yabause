#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class ClrmacTest : public ::testing::Test {
 protected:
  SH2Interface_struct* pctx_;

  ClrmacTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~ClrmacTest() {   
  }   

virtual void SetUp() {
  
}

virtual void TearDown() {

}

};


TEST_F(ClrmacTest, normal) {

  MSH2->regs.MACH = (0x00000FF);
  MSH2->regs.MACL = (0xFF00000);

  MappedMemoryWriteWord( 0x06000000, 0x0028 );  // clrmac
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop

  MSH2->regs.PC = ( 0x06000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x00000000, MSH2->regs.MACH );
  EXPECT_EQ( 0x00000000, MSH2->regs.MACL );
}



}  // namespacegPtr
