#ifndef OPEN_CLOSED_HPP_nhnrg1
#define OPEN_CLOSED_HPP_nhnrg1

#include <string>
#include <vector>

enum class Color
{
    Red,
    Green,
    Blue
};

enum class Size
{
    Small,
    Medium,
    Large
};

namespace SolidDesign
{
    struct Product
    {
        std::string name;
        Color color;
        Size size;
    };

    struct ProductFilter
    {
        std::vector<Product*> byColor(std::vector<Product*> items, Color color)
        {
            std::vector<Product*> result;

            for (const auto& i: items)
                if (i->color == color)
                    result.push_back(i);
            
            return result;
        }

        std::vector<Product*> bySize(std::vector<Product*> items, Size size)
        {
            std::vector<Product*> result;

            for (const auto& i: items)
                if (i->size == size)
                    result.push_back(i);
            
            return result;
        }

        std::vector<Product*> byColorAndSize(std::vector<Product*> items, Color color, Size size)
        {
            std::vector<Product*> result;

            for (const auto& i: items)
                if (i->color == color && i->size == size)
                    result.push_back(i);
            
            return result;
        }
    };

    template <typename T>
    struct AndSpecification;

    template<typename T> struct Specification
    {
        virtual bool isSatisfied(T* item) = 0;

        AndSpecification<T> operator &&(Specification<T>&& other)
        {
            return AndSpecification<T>(*this, other);
        }
    };


    template<typename T> struct Filter
    {
        virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) = 0;
    };

    
    struct FilterBase : public Filter<Product>
    {
        std::vector<Product*> filter(std::vector<Product*> items, Specification<Product>& spec) override
        {
            std::vector<Product*> result;
            for (auto& item : items)
                if (spec.isSatisfied(item))
                    result.push_back(item);
            
            return result;
        }
    };


    struct ColorSpecification : public Specification<Product>
    {
        Color color;
        ColorSpecification(Color _color) : color(_color) {}

        bool isSatisfied(Product* item) override
        {
            return item->color == color;
        }
    };

    struct SizeSpecification : public Specification<Product>
    {
        Size size;
        SizeSpecification(Size _size) : size(_size) {}

        bool isSatisfied(Product* item) override
        {
            return item->size == size;
        }
    };


    template <typename T> struct AndSpecification : public Specification<T>
    {
        Specification<T>& first;
        Specification<T>& second;

        AndSpecification(Specification<T>& _first, 
            Specification<T>& _second
        ) : first(_first), second(_second) {}

        bool isSatisfied(Product* item) override
        {
            return first.isSatisfied(item) && second.isSatisfied(item);
        }
    };
}

#endif /* end of include guard : OPEN_CLOSED_HPP_nhnrg1 */