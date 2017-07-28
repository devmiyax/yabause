#include "gtest/gtest.h"
#include <core.h>
#include "sh2core.h"
#include "debug.h"
#include "yabause.h"
extern "C" {
extern void initEmulation();
}
namespace {

class JsrTest : public ::testing::Test {
 protected:
   SH2Interface_struct* pctx_;

  JsrTest() {
    initEmulation();
    pctx_ = SH2Core;
  }

  virtual ~JsrTest() {
  }   

virtual void SetUp() {
  
}

virtual void TearDown() {

}

};

TEST_F(JsrTest, jsr) {

  MSH2->regs.R[1]=0x03216721;

  MappedMemoryWriteWord( 0x06000000, 0x410B );
  MappedMemoryWriteWord( 0x06000002, 0x000b );
  MappedMemoryWriteWord( 0x06000004, 0x0009 );

  MSH2->regs.PC = ( 0x06000000 );
  MSH2->regs.SR.all = ( 0x00000000 );
  SH2Exec(MSH2, 1);

  EXPECT_EQ( 0x03216721, MSH2->regs.R[1] );
  EXPECT_EQ( 0x03216721, MSH2->regs.PC );
  EXPECT_EQ( 0x06000004, MSH2->regs.PR  );
}

}  // namespacegPtr
