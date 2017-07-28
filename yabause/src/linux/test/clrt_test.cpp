#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class ClrtTest : public ::testing::Test {
 protected:
  SH2Interface_struct* pctx_;

  ClrtTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~ClrtTest() {    
  }   

virtual void SetUp() {
  
}

virtual void TearDown() {

}

};


TEST_F(ClrtTest, normal) {

  MSH2->regs.SR.all = (0x00003F3);

  MappedMemoryWriteWord( 0x06000000, 0x0008 );  // clrt
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop

  MSH2->regs.PC = ( 0x06000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x000003F2, MSH2->regs.SR.all );
}



}  // namespacegPtr
