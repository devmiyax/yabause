#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class MoviTest : public ::testing::Test {
 protected:
   SH2Interface_struct* pctx_;

  MoviTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~MoviTest() {
  }   

virtual void SetUp() {
 
  
}

virtual void TearDown() {


}

};

TEST_F(MoviTest, normal) {


  MSH2->regs.R[0]=0x0000006d;


  // mova
  MappedMemoryWriteWord( 0x0600024c, 0xe06e );
  MappedMemoryWriteWord( 0x0600024e, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000250, 0x0009 );  // nop

  MSH2->regs.PC =( 0x0600024c );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x0000006e, MSH2->regs.R[0] );

}


TEST_F(MoviTest, m) {


  MSH2->regs.R[0]=0x0000006d;


  // mova
  MappedMemoryWriteWord( 0x0600024c, 0xe081 );
  MappedMemoryWriteWord( 0x0600024e, 0x000b );  // rts
  MappedMemoryWriteWord( 0x06000250, 0x0009 );  // nop

  MSH2->regs.PC =( 0x0600024c );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0xFFFFFF81, MSH2->regs.R[0] );

}

}  // namespace
