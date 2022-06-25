#ifndef FLUENT_BUILDER_HPP_jvacd0
#define FLUENT_BUILDER_HPP_jvacd0

#include <string>
#include <vector>
#include <sstream>

namespace Builder::Fluent
{
    class HTMLBuilder;
    class HTMLElement
    {
    public:
        HTMLElement() {}

        HTMLElement(const std::string& name, const std::string& text) : name(name), text(text) {}

        std::string str(int indent = 0) const
        {
            std::ostringstream oss;
            std::string i (indentSize * indent, ' ');
            oss << i << '<' << name << '>' << std::endl;
            if (text.size() > 0)
                oss << std::string(indentSize * (indent + 1), ' ') << text << std::endl;

            for (const auto& e: elements)
                oss << e.str(indent + 1);
            
            oss << i << "</" << name << '>' << std::endl;
            return oss.str();
        }

        static HTMLBuilder build(std::string rootName)
        {
            return {rootName};
        }

    public:
        std::string name, text;
        std::vector<HTMLElement> elements;
        const size_t indentSize = 4;
    };

    class HTMLBuilder
    {
    public: 
        HTMLBuilder(std::string rootName) { root.name = rootName; }

        void addChild(std::string childName, std::string childText)
        {
            HTMLElement e {childName, childText};
            root.elements.emplace_back(e);
        }

        std::string str() const { return root.str(); }

        operator HTMLElement() const { return root; }
    
    public:
        HTMLElement root;
    };
}

#endif /* end of include guard : FLUENT_BUILDER_HPP_jvacd0 */