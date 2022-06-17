#include <gtest/gtest.h>
#include <solid_design/single_responsibility.hpp>

TEST(SingleResponbilityTest, JournalTest)
{
    SolidDesign::Journal jr{"Hi Everyone"};

    jr.addEntry("Lorem ipsum");
    jr.addEntry("Dolor sit Amet");

    ASSERT_TRUE(jr.getEntries().size() == 2);
    ASSERT_TRUE(jr.getTitle() == "Hi Everyone");

    std::vector<std::string> actual {
        "1: Lorem ipsum",
        "2: Dolor sit Amet"
    };
    
    ASSERT_EQ(jr.getEntries().size(), actual.size());

    size_t index = 0;
    for (size_t i = 0; i < actual.size(); ++i)
    {
        ASSERT_EQ(actual[i], jr.getEntries()[i]) << index;
        ++index;
    }
}