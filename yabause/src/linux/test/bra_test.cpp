#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class BraTest : public ::testing::Test {
 protected:
  SH2Interface_struct* pctx_;

  BraTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~BraTest() {    
  }   

virtual void SetUp() {
   
}

virtual void TearDown() {
}

};

TEST_F(BraTest, normal) {


  // BRA
  MappedMemoryWriteWord( 0x06002E00, 0xA123 );
  MappedMemoryWriteWord( 0x06002E02, 0x0009 );  // nop

  MSH2->regs.PC = ( 0x06002E00 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x0600304A, MSH2->regs.PC );

  // BRA
  MappedMemoryWriteWord( 0x06000220, 0xA015 );
  MappedMemoryWriteWord( 0x06000222, 0x277A );  // nop

  MSH2->regs.PC = ( 0x06000220 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x0600024E, MSH2->regs.PC );

}

TEST_F(BraTest, negative) {
  // BRA
  MappedMemoryWriteWord( 0x06002E00, 0xAFF5 );
  MappedMemoryWriteWord( 0x06002E02, 0x0009 );  // nop

  MSH2->regs.PC = ( 0x06002E00 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x06002DEE, MSH2->regs.PC );
}

TEST_F(BraTest, braf) {
  // BRAF
  MSH2->regs.R[1]=0x00106520; //source

  MappedMemoryWriteWord( 0x06002E00, 0x0123 );
  MappedMemoryWriteWord( 0x06002E02, 0x0009 );  // nop

  MSH2->regs.PC = ( 0x06002E00 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x06109324, MSH2->regs.PC );
}

TEST_F(BraTest, braf_negative) {
  // BRAF
  MSH2->regs.R[1]=0xFFFFFFFC; //source

  MappedMemoryWriteWord( 0x06002E00, 0x0123 );
  MappedMemoryWriteWord( 0x06002E02, 0x0009 );  // nop

  MSH2->regs.PC = ( 0x06002E00 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x06002E00, MSH2->regs.PC );
}

}  // namespace
