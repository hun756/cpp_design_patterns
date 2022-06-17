#include <gtest/gtest.h>
#include <solid_design/open_closed.hpp>
#include <vector>

TEST(OpenClosedPrinciple, ProductFilter)
{
    SolidDesign::Product apple {"Apple", Color::Green, Size::Small};
    SolidDesign::Product tree {"Tree", Color::Green, Size::Large};
    SolidDesign::Product house {"House", Color::Blue, Size::Large};

    std::vector<SolidDesign::Product*> items {
        &apple, &tree, &house
    };

    SolidDesign::ProductFilter pf;

    auto greenObjs = pf.byColor(items, Color::Green);

    std::vector<std::string> actual {
        "Apple", "Tree"
    };

    size_t index = 0;
    for (const auto& i: greenObjs)
    {
        ASSERT_TRUE(i->name == actual[index]) << index;
        ++index;
    }
}

TEST(OpenClosedPrinciple, ProductFilterWSpecifization)
{
    SolidDesign::Product apple {"Apple", Color::Green, Size::Small};
    SolidDesign::Product tree {"Tree", Color::Green, Size::Large};
    SolidDesign::Product house {"House", Color::Blue, Size::Large};

    std::vector<SolidDesign::Product*> items {
        &apple, &tree, &house
    };

    SolidDesign::FilterBase bestFilter;
    SolidDesign::ColorSpecification greenColorSpec(Color::Green);
    SolidDesign::SizeSpecification sizeSpec(Size::Large);
    SolidDesign::AndSpecification<SolidDesign::Product> greenAndLarge(greenColorSpec, sizeSpec);


    std::vector<std::string> actual {
        "Apple", "Tree"
    };

    size_t index = 0;
    for (const auto& i: bestFilter.filter(items, greenColorSpec))
    {
        ASSERT_TRUE(i->name == actual[index]) << index;
        ++index;
    }

    std::vector<std::string> greendAndLarge {
        "Tree"
    };

    index = 0;
    for (const auto& i: bestFilter.filter(items, greenAndLarge))
    {
        ASSERT_TRUE(i->name == greendAndLarge[index]) << index;
        ++index;
    }

    auto spec = SolidDesign::ColorSpecification(Color::Green)
        && SolidDesign::SizeSpecification(Size::Large);

    index = 0;
    for (const auto& i: bestFilter.filter(items, spec))
    {
        ASSERT_TRUE(i->name == greendAndLarge[index]) << index;
        ++index;
    }
}