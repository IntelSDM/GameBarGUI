#include "pch.h"
#include "Entity.h"
class Config
{
public:
	Entity Entity1;
	Entity Entity2;

    void ToJson(json& j) const
    {
        j = json{
            {"Entity1", json{}},
            {"Entity2", json{}}
        };

        Entity1.ToJson(j["Entity1"]);
        Entity2.ToJson(j["Entity2"]);
    }

    // Function to populate the Config object from JSON
    void FromJson(const json& j)
    {
        if (j.contains("Entity1"))
            Entity1.FromJson(j["Entity1"]);
        if (j.contains("Entity2"))
            Entity2.FromJson(j["Entity2"]);
    }

};
