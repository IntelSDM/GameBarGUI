#include "pch.h"
//jsonize
class Entity
{
public:
	bool DrawBox = true;
	bool DrawName = true;
	std::map<std::string, DWORD> Colour = { {"test123",0},{"test321",1}};

    void ToJson(json& j) const
    {
        j = json{
            {"DrawBox", DrawBox},
            {"DrawName", DrawName},
            {"Colour", Colour}
        };
    }

    // Convert JSON to Entity object
    void FromJson(const json& j)
    {
        if (j.contains("DrawBox"))
            DrawBox = j["DrawBox"];

        if (j.contains("DrawName"))
            DrawName = j["DrawName"];

        if (j.contains("Colour"))
            Colour = j["Colour"].get<std::map<std::string, DWORD>>();
    }
};
