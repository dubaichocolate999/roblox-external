#pragma once
#include <vector>
#include <string>

namespace whitelist {

    static std::vector<std::string> whitelist;

    static void add_whitelist(const std::string& name) {
        if (std::find(whitelist.begin(), whitelist.end(),name) == whitelist.end())
            whitelist.push_back(name);
    }

    static void remove_whitelist(const std::string& name) {
        auto it = std::find(whitelist.begin(), whitelist.end(), name);
        if (it != whitelist.end())
            whitelist.erase(it);
    }

    static bool is_whitelisted(const std::string& name) {
        for (const std::string& whitelisted : whitelist) {
            if (whitelisted == name)
                return true;
        }

        return false;
    }

}