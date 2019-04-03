#include "gmock/gmock.h"

class EvaluatedExpression;
std::map<std::string, std::function<std::shared_ptr<EvaluatedExpression>(std::vector < std::shared_ptr < EvaluatedExpression >> args)>> env;

int main(int argc, char* argv[]) {
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
