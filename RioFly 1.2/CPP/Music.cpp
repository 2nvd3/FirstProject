#include "../Header/Music.h"

std::vector<std::string> SetMusics()
{
	std::vector<std::string> songs;
	for (int i = 0; i < 10; i++)
	{
        std::string temp_Name = "Audio/Song_";
        std::string num = std::to_string(i);

        temp_Name += num + ".ogg";
        songs.push_back(temp_Name);
    }
    return songs;
}
