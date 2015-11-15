#include <gtest/gtest.h>
#include <cstring>
#include "Lead.h"
#include "Insulator.h"
#include "Chain.h"



class ChainTest: public::testing::Test
{
protected:

    double V;
    Lead lL, lR;
    Insulator B1;
    string T1, T2;
    Chain wire;


    virtual void SetUp()
    {
        V = -0.6;
        lL = Lead(1.2, 2.0, -0.4, -0.4, 300, 0, 0);
        T1 = "-0.4, 0.0; 0.0, -0.4";
        B1 = Insulator(5.4, 5.4, -0.4, -0.4, 5, 0, 0, V);
        T2 = "-0.4, 0.0; 0.0, -0.4";
        lR = Lead(1.2, 2.0, -0.4, -0.4, 300, M_PI/2, V);
        wire = Chain(lL, T1, B1, T2, lR);
    }
};



TEST_F(ChainTest,unname_xaa)
{
    EXPECT_FLOAT_EQ(4.123, wire.unname_x(0.0, 0.0, -0.2));
    EXPECT_FLOAT_EQ(4.123, wire.unname_x(0.0, 0.0, -0.2));
    EXPECT_FLOAT_EQ(4.123, wire.unname_x(0.0, 0.0, -0.2));
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
