#ifndef SINGLE_RESPONSIBLITY_PRINCIPLES_HPP_n2oz9y
#define SINGLE_RESPONSIBLITY_PRINCIPLES_HPP_n2oz9y

#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

namespace SolidDesign
{
    class Journal
    {
    public:
        /**
         * @brief Construct a new Journal object
         * 
         * @param _title 
         *  Title for entries.
         */
        Journal(const std::string& _title) : title(_title) {}

        /**
         * @brief 
         *  This methods add entry to member element entries
         * 
         * @param _entry
         *  
         */
        void addEntry(const std::string& _entry)
        {
            static int count = 1;
            entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + _entry);
        }

        /**
         * @brief 
         *  Save entries to file.
         * 
         * @param _filename 
         */
        void save(const std::string& fileName)
        {
            std::ofstream out {fileName};
            for (const auto& e : entries)
                out << e << std::endl;
        }

        // getters -----
        std::string getTitle() const { return title; }
        std::vector<std::string> getEntries() const { return entries; }
    
    private:
        std::string title;
        std::vector<std::string> entries;
    };
    

    class PersistenceManager
    {
    public:
        static void save(const Journal& j, const std::string& fileName)
        {
            std::ofstream out {fileName};
            for (const auto& e : j.getEntries())
                out << e << std::endl;
        }
    };
}

#endif /* end of include guard : SINGLE_RESPONSIBLITY_PRINCIPLES_HPP_n2oz9y */