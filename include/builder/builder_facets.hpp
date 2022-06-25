#ifndef BUILDER_FACETS_HPP_ev3tqc
#define BUILDER_FACETS_HPP_ev3tqc

#include <string>
#include <iostream>

namespace Builder
{
    class PersonBuilder;
    class Person
    {
        // address
        std::string street_address, post_code, city;

        // employment
        std::string company_name, position;
        int annual_income = 0;

        Person()
        {
            std::cout << "Person created\n";
        }

    public:
        ~Person()
        {
            std::cout << "Person destroyed\n";
        }

        static PersonBuilder create();

        Person(Person &&other)
            : street_address{move(other.street_address)},
              post_code{move(other.post_code)},
              city{move(other.city)},
              company_name{move(other.company_name)},
              position{move(other.position)},
              annual_income{other.annual_income}
        {
        }

        Person &operator=(Person &&other)
        {
            if (this == &other)
                return *this;
            street_address = move(other.street_address);
            post_code = move(other.post_code);
            city = move(other.city);
            company_name = move(other.company_name);
            position = move(other.position);
            annual_income = other.annual_income;
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const Person &obj)
        {
            return os
                   << "street_address: " << obj.street_address
                   << " post_code: " << obj.post_code
                   << " city: " << obj.city
                   << " company_name: " << obj.company_name
                   << " position: " << obj.position
                   << " annual_income: " << obj.annual_income;
        }

        friend class PersonBuilder;
        friend class PersonAddressBuilder;
        friend class PersonJobBuilder;
    };

    class PersonAddressBuilder;
    class PersonJobBuilder;

    class PersonBuilderBase
    {
    protected:
        Person &person;
        explicit PersonBuilderBase(Person &person)
            : person{person}
        {
        }

    public:
        operator Person() const
        {
            return std::move(person);
        }

        // builder facets

        PersonAddressBuilder lives() const
        {
            return PersonAddressBuilder{person};
        }

        PersonJobBuilder works()
        {
            return PersonJobBuilder{person};
        }
    };

    class PersonBuilder : public PersonBuilderBase
    {
        Person p;

    public:
        PersonBuilder() : PersonBuilderBase{p}
        {
        }
    };

    class PersonAddressBuilder : public PersonBuilderBase
    {
        typedef PersonAddressBuilder Self;

    public:
        explicit PersonAddressBuilder(Person &person)
            : PersonBuilderBase{person}
        {
        }

        Self &at(std::string street_address)
        {
            person.street_address = street_address;
            return *this;
        }

        Self &with_postcode(std::string post_code)
        {
            person.post_code = post_code;
            return *this;
        }

        Self &in(std::string city)
        {
            person.city = city;
            return *this;
        }
    };

    class PersonJobBuilder : public PersonBuilderBase
    {
        typedef PersonJobBuilder Self;

    public:
        explicit PersonJobBuilder(Person &person)
            : PersonBuilderBase{person}
        {
        }

        Self &at(std::string company_name)
        {
            person.company_name = company_name;
            return *this;
        }

        Self &as_a(std::string position)
        {
            person.position = position;
            return *this;
        }

        Self &earning(int annual_income)
        {
            person.annual_income = annual_income;
            return *this;
        }
    };
}

#endif /* end of include guard : BUILDER_FACETS_HPP_ev3tqc */