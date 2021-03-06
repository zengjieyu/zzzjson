#include "../../test.h"

#include "cJSON/cJSON.h"

class cjsonTest : public Test
{
  public:
    cjsonTest(const std::string &path) : Test("cjson", path){};
    cjsonTest(const std::vector<std::string> &jsons) : Test("cjson", jsons){};
    virtual bool Parse(const char *json, unsigned long long *ms)
    {
        uint64_t now = Now();
        cJSON *root = cJSON_ParseWithOpts(json, nullptr, static_cast<cJSON_bool>(true));
        *ms = Now() - now;
        if (root == 0)
            return false;
        return true;
    }
    virtual bool Stringify(const char *json, unsigned long long *ms)
    {
        cJSON *root = cJSON_ParseWithOpts(json, nullptr, static_cast<cJSON_bool>(true));
        if (root == 0)
            return false;
        uint64_t now = Now();
        cJSON_PrintBuffered(root, 4096, static_cast<cJSON_bool>(false));
        *ms = Now() - now;
        return true;
    }
    virtual bool All(const char *json, unsigned long long *ms)
    {
        uint64_t now = Now();
        {
            cJSON *root = cJSON_ParseWithOpts(json, nullptr, static_cast<cJSON_bool>(true));
            if (root == 0)
                return false;
            uint64_t now = Now();
            cJSON_PrintBuffered(root, 4096, static_cast<cJSON_bool>(false));
        }
        *ms = Now() - now;
        return true;
    }
};