#ifndef DEPENDENCY_INVERSION_HPP_ozf1pm
#define DEPENDENCY_INVERSION_HPP_ozf1pm

#include <string>
#include <vector>
#include <tuple>


namespace SolidDesign
{
    enum class Relationship
    {
        Parent,
        Child,
        Sibling
    };

    struct Person
    {
        std::string name;
    };

    struct RelationshipBrowser
    {
        virtual std::vector<Person> findAllChilrenOf(const std::string& name) = 0;
    };

    struct Relationships : RelationshipBrowser
    {
        std::vector<std::tuple<Person, Relationship, Person>> relations;

        void addParentAndChild(const Person& parent, const Person& child)
        {
            relations.push_back(std::make_tuple(parent, Relationship::Parent, child));
            relations.push_back(std::make_tuple(child, Relationship::Child, parent));
        }

        std::vector<Person> findAllChilrenOf(const std::string& name)
        {
            std::vector<Person> result;

            for (auto&& [first, rel, second]: relations)
                if (first.name == name && rel == Relationship::Parent)
                    result.push_back(second);

            return result;
        }
    };
    
}

#endif /* end of include guard : DEPENDENCY_INVERSION_HPP_ozf1pm */