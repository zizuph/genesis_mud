inherit "/d/Khalakhor/lib/weather_server";

#include "/d/Khalakhor/sys/weather.h" 

void
create_weather_server() 
{
    set_save_file("/d/Khalakhor/igneous/open/weather/serverinfo");
}

void
change_weather_hook(string region)
{
    //  Region4 always has fog
    if (region == "region4")
	Info[region][CURRENT_WEATHER] = FOG;
    // Region3 is Sunny 50% of the time
    else if (region == "region3" && !random(2))
	Info[region][CURRENT_WEATHER] = SUNNY;
    else
	::change_weather_hook(region);
}
