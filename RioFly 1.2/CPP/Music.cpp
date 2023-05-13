
#include "../Header/Music.h"

std::vector<std::string> SetMusics()
{
	std::vector<std::string> Songname;
	for (int i = 0; i < 10; i++)
	{
        std::string temp_Name = "Audio/Song_";
        std::string num_String = std::to_string(i);

        temp_Name += num_String + ".ogg";
        Songname.push_back(temp_Name);
    }
    return Songname;
}
