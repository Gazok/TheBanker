#include "DialogueTree.hpp"
#include <sstream>

DialogueTree::DialogueTree(boost::property_tree::ptree const& dTree)
{
    for(auto line : dTree.get_child("dialogue.text"))
    {
        std::stringstream s;
        s << line.second.data();
        _text.push_back(s.str());
    }

    boost::optional<std::string> optionsExist 
        = dTree.get_optional<std::string>("dialogue.options");

    if(optionsExist.is_initialized())
    {
        for(auto option : dTree.get_child("dialogue.options"))
        { 
            std::stringstream s;
            s << option.second.data();
            _options.push_back(s.str());
        }

        for(auto response : dTree.get_child("dialogue.responses"))
        {
            _responses.push_back(DialogueTree(response.second));
        }
    }
} 
