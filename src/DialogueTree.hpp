#pragma once
#ifndef DIALOGUETREE_H
#define DIALOGUETREE_H

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

class DialogueTree
{
public:
    DialogueTree(boost::property_tree::ptree const&); 

    std::vector<std::string> const& getText()    const { return _text; }
    std::vector<std::string> const& getOptions() const { return _options; }
    DialogueTree const* chooseOption(int i)      const { return &_responses[i]; }
private:
    std::vector<std::string> _options;
    std::vector<DialogueTree> _responses;
    std::vector<std::string> _text; 
};
#endif
