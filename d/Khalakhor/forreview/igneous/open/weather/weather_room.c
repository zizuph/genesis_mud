inherit "/d/Khalakhor/std/new_std_room";

#include "/d/Khalakhor/sys/weather.h"

void
create_khalakhor_room()
{
    set_short("A test room for the weather system");
    set_long("A vast expanse of plains goes as far as the eye can see.  "+
      "A number of rabbits bounce around the plains nibbling on the "+
      "various tall grasses and wildflowers.\n");

    add_item(({"plains","plain","grasses", "grass"}), "@@plains_desc@@");
    add_item(({"flowers","wildfowers","flower","wildflower"}),"@@flowers@@");
    add_item(({"rabbit","rabbits"}), "@@rabbits@@");
}

string
plains_desc()
{
    int weather = WEATHER_MASTER->query_weather(query_weather_region());
    string extra_bit = "";

    // Is it windy?
    if (weather & WIND || weather & GUSTS)
        extra_bit += " wind-blown,";
    // Is it raining?
    if (weather & RAIN)
        extra_bit += " rain-soaked,";
    // Is it snowing?
    if (weather & SNOW)
        extra_bit += " snow-covered,";

    return "A vast,"+extra_bit+" grassy plain stretches as far "+
        "the eye can see.\n";    
}

string
flowers()
{
    int weather = WEATHER_MASTER->query_weather(query_weather_region());

    if (weather & SNOW)
        return "A few wildflowers manage to poke their way through "+
            "the snow.\n";

    if (weather & SUN)
        return "Numerous wildflowers stretch out towards the Sun.\n";

    return "Many wildflowers populate the plains.\n";
}

string
rabbits()
{
    int weather = WEATHER_MASTER->query_weather(query_weather_region());

    switch(weather)
    {
    case SUNNY:
        return "Many rabbits leap about, playing in the bright sunlight.\n";
    case SHOWERS:
    case RAINY:
    case TSTORM:
        return "A few rabbits scurry about in the rain.\n";
    case FLURRY:
    case BLIZZARD:
    case SNOWY:
        return "A few rabbits leap about the snow-covered plains.\n";
    default:
        return "A bunch of rabbits nibble the grass here.\n";
    }
}	
