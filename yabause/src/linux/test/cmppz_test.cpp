#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class CmpPzTest : public ::testing::Test {
 protected:
   SH2Interface_struct* pctx_;

  CmpPzTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~CmpPzTest() { 
  }   

virtual void SetUp() {
  
}

virtual void TearDown() {

}

};


TEST_F(CmpPzTest, normal) {

  MSH2->regs.R[1]=0x0001; // m
  MSH2->regs.SR.all = (0x00000E0);

  MappedMemoryWriteWord( 0x06000000, 0x4111 );  // cmppl R[1]
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop

  MSH2->regs.PC = ( 0x06000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x000000E1, MSH2->regs.SR.all );
}

TEST_F(CmpPzTest, Zero) {

  MSH2->regs.R[1]=0x0; // m
  MSH2->regs.SR.all = (0x00000E0);

  MappedMemoryWriteWord( 0x06000000, 0x4111 );  // cmppz R[1]
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop

  MSH2->regs.PC = ( 0x06000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x000000E1, MSH2->regs.SR.all );
}

TEST_F(CmpPzTest, min) {

  MSH2->regs.R[1]=0xFFFFFFFE; // m
  MSH2->regs.SR.all = (0x00000E1);

  MappedMemoryWriteWord( 0x06000000, 0x4111 );  // cmppz R[1]
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop

  MSH2->regs.PC = ( 0x06000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x000000E0, MSH2->regs.SR.all );
}


}  // namespacegPtr
