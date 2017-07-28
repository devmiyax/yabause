#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class BtTest : public ::testing::Test {
 protected:
  SH2Interface_struct* pctx_;

  BtTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~BtTest() {    
  }   

virtual void SetUp() {
 
  
}

virtual void TearDown() {


}

};

TEST_F(BtTest, normal) {

  MappedMemoryWriteWord( 0x06000246, 0x8902 ); 

  MSH2->regs.PC = ( 0x06000246 );
  MSH2->regs.SR.all = ( 0x0 );
  SH2Exec(MSH2, 1);

 EXPECT_EQ( 0x06000248, MSH2->regs.PC );
 EXPECT_EQ( 0x0, MSH2->regs.SR.all );

  MappedMemoryWriteWord( 0x06000246, 0x8902 ); 

  MSH2->regs.PC = ( 0x06000246 );
  MSH2->regs.SR.all = ( 0x1 );
  SH2Exec(MSH2, 1);

 EXPECT_EQ( 0x0600024E, MSH2->regs.PC );
 EXPECT_EQ( 0x1, MSH2->regs.SR.all );

  MappedMemoryWriteWord( 0x06000246, 0x8982 ); 

  MSH2->regs.PC = ( 0x06000246 );
  MSH2->regs.SR.all = ( 0x0 );
  SH2Exec(MSH2, 1);

 EXPECT_EQ( 0x06000248, MSH2->regs.PC );
 EXPECT_EQ( 0x0, MSH2->regs.SR.all );

  MappedMemoryWriteWord( 0x06000246, 0x8982 ); 

  MSH2->regs.PC = ( 0x06000246 );
  MSH2->regs.SR.all = ( 0x1 );
  SH2Exec(MSH2, 1);

 EXPECT_EQ( 0x0600014E, MSH2->regs.PC );
 EXPECT_EQ( 0x1, MSH2->regs.SR.all );

}

TEST_F(BtTest, bts) {

  MappedMemoryWriteWord(0x06002E4C,0x8D0B);
  MappedMemoryWriteWord( 0x06002E4E, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06002E50, 0x0009 );  // nop 

  MSH2->regs.PC = ( 0x06002E4C );
  MSH2->regs.SR.all = ( 0x000001);
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x06002E4C+4+(0xB<<1), MSH2->regs.PC );

  MappedMemoryWriteWord(0x06002E4C,0x8D0B);
  MappedMemoryWriteWord( 0x06002E4E, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06002E50, 0x0009 );  // nop 

  MSH2->regs.PC = ( 0x06002E4C );
  MSH2->regs.SR.all = ( 0x000000);
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x06002E4C+4, MSH2->regs.PC );

  MSH2->regs.R[3]=0x2;

  MappedMemoryWriteWord(0x06002E4C,0x8D8B);
  MappedMemoryWriteWord( 0x06002E4E, 0x7304 );  // add #4, r3
  MappedMemoryWriteWord( 0x06002E50, 0x0009 );  // nop 

  MSH2->regs.PC = ( 0x06002E4C );
  MSH2->regs.SR.all = ( 0x000001);
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x6, MSH2->regs.R[3] );
  EXPECT_EQ( 0x06002E4C+4+(0xFFFFFF8B<<1), MSH2->regs.PC );

  MappedMemoryWriteWord(0x06002E4C,0x8D8B);
  MappedMemoryWriteWord( 0x06002E4E, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06002E50, 0x0009 );  // nop 

  MSH2->regs.PC = ( 0x06002E4C );
  MSH2->regs.SR.all = ( 0x000000);
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x06002E4C+4, MSH2->regs.PC );

}

}  // namespace
