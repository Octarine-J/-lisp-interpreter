#include <gmock/gmock.h>
#include "interpreter/eval_error.h"

using namespace ::testing;

class EvalErrorTest : public Test {

};

TEST_F(EvalErrorTest, UnknownApplicative) {
    try {
        throw eval_error::UnknownApplicative("func");
    } catch (eval_error::EvalError &e) {
        ASSERT_THAT(e.what(), StrEq("Unknown function: 'func'"));
    }
}
