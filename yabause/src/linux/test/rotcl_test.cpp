#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class RotclTest : public ::testing::Test {
 protected:
   SH2Interface_struct* pctx_;

  RotclTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~RotclTest() {   
  }

virtual void SetUp() {
  printf("RotclTest::SetUp\n");
  
}

virtual void TearDown() {
  printf("RotclTest::TearDown\n");

}

};

TEST_F(RotclTest, normal) {

  MSH2->regs.R[0]=0x00000001;

  // rtcl R[0]
  MappedMemoryWriteWord( 0x06000000, 0x4024 );
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop

  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x00, (MSH2->regs.SR.all&0x01) );
  EXPECT_EQ( 0x02, MSH2->regs.R[0] );

}



TEST_F(RotclTest, carry) {

  MSH2->regs.R[0]=0x80000000;

  // rtcl R[0]
  MappedMemoryWriteWord( 0x06000000, 0x4024 );
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop
  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x01, (MSH2->regs.SR.all&0x01) );
  EXPECT_EQ( 0x00, MSH2->regs.R[0] );

}

TEST_F(RotclTest, from_carry) {

  MSH2->regs.R[0]=0x00000000;

  // rtcl R[0]
  MappedMemoryWriteWord( 0x06000000, 0x4024 );
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop
  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x000001 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x00, (MSH2->regs.SR.all&0x01) );
  EXPECT_EQ( 0x01, MSH2->regs.R[0] );

}

TEST_F(RotclTest, carry_from_carry) {

  MSH2->regs.R[0]=0x80000000;

  // rtcl R[0]
  MappedMemoryWriteWord( 0x06000000, 0x4024 );
  MappedMemoryWriteWord( 0x06000002, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000004, 0x0009 );  // nop
  MSH2->regs.PC =( 0x06000000 );
  MSH2->regs.SR.all =( 0x000001 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x01, (MSH2->regs.SR.all&0x01) );
  EXPECT_EQ( 0x01, MSH2->regs.R[0] );

}


}  // namespace
