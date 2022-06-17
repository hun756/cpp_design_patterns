#ifndef INTERFACE_SEGREGATION_HPP_i00vf1
#define INTERFACE_SEGREGATION_HPP_i00vf1

namespace SolidDesign
{
    struct Document;

    struct BadIMachine
    {
        virtual void print(Document& doc);
        virtual void scan(Document& doc);
        virtual void fax(Document& doc);
    };

    struct BadMFP: public BadIMachine
    {
        void print(Document& doc) override
        {
            // ok
        }

        void scan(Document& doc) override
        {
        }

        void fax(Document& doc) override
        {
        }
    };

    struct BadScanner: public BadIMachine
    {
        void print(Document& doc) override
        {
        }

        void scan(Document& doc) override
        {
            // Ok..
        }

        void fax(Document& doc) override
        {
        }
    };

    struct IPrinter
    {
        virtual void print(Document& doc);
    };

    struct IScanner
    {
        virtual void scan(Document& doc);
    };

    struct IFax
    {
        virtual void fax(Document& doc);
    };

    struct IMachine: IPrinter, IScanner {};

    struct Machine: IMachine
    {
        IPrinter& printer;
        IScanner& scanner;

        Machine(IPrinter& printer, IScanner& scanner) : printer(printer), scanner(scanner) {} 

        void print(Document& doc) override
        {
            printer.print(doc);
        }

        void scan(Document& doc) override
        {
            scanner.scan(doc);
        }
    };
}

#endif /* end of include guard : INTERFACE_SEGREGATION_HPP_i00vf1 */