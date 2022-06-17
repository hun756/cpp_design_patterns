#include <gtest/gtest.h>
#include <solid_design/liskov_substitution.hpp>

TEST(LiskovSubstitutionPrinciple, Rectangle)
{
    // auto ll_process = [](SolidDesign::Rectangle& r) -> void { 
    // };

    SolidDesign::Rectangle r{3, 4};
    int w = r.getWidth();
    r.setHeight(10);
    ASSERT_TRUE(w * 10 == r.area());

    SolidDesign::Square sq {5};
    sq.setHeight(10);
    w = sq.getWidth();

    ASSERT_TRUE(w * 10 == sq.area());
}