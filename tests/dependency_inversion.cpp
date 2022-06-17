#include <gtest/gtest.h>
#include <solid_design/dependency_inversion.hpp>

TEST(DependencyInversion, Relationship)
{
    SolidDesign::Person parent{"John"};
    SolidDesign::Person child1{"Chris"}, child2{"Matt"};

    SolidDesign::Relationships relationship;

    relationship.addParentAndChild(parent, child1);
    relationship.addParentAndChild(parent, child2);

    auto val = relationship.findAllChilrenOf("John");

    ASSERT_TRUE(val.size() == 2);

    std::vector<std::string> actual {
        "Chris", "Matt"
    };

    size_t index = 0;
    
    for (size_t i = 0; i < val.size(); i++)
    {
        ASSERT_TRUE(val[i].name == actual[i]) << index;
        ++index;
    }
    
}