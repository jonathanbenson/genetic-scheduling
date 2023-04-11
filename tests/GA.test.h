
#include "acutest.h"
#include "GA.h"

void test_GA_Softmax() {
    // Test case 1: Test with all positive inputs
    std::vector<double> input1 = {1.0, 2.0, 3.0};
    std::vector<double> expected_output1 = {0.09003057317038046, 0.24472847105479764, 0.6652409557748219};
    std::vector<double> output1 = Softmax(input1);
    for (int i = 0; i < output1.size(); i++) {
        TEST_CHECK(std::abs(output1[i] - expected_output1[i]) < 1e-6);
    }

    // Test case 2: Test with all negative inputs
    std::vector<double> input2 = {-1.0, -2.0, -3.0};
    std::vector<double> expected_output2 = {0.6652409557748219, 0.24472847105479764, 0.09003057317038046};
    std::vector<double> output2 = Softmax(input2);
    for (int i = 0; i < output2.size(); i++) {
        TEST_CHECK(std::abs(output2[i] - expected_output2[i]) < 1e-6);
    }

    // Test case 3: Test with mixed inputs
    std::vector<double> input3 = {-1.0, 2.0, -3.0};
    std::vector<double> expected_output3 = {0.047123416524664, 0.94649912255289, 0.0063774609224423};
    std::vector<double> output3 = Softmax(input3);

    for (int i = 0; i < output3.size(); i++) {
        TEST_CHECK(std::abs(output3[i] - expected_output3[i]) < 1e-6);
    }
}

