
#include "/d/Faerun/defs.h"

int precipitation;
int wind;
int clouds;
int temperature;
int winddir;

int
query_precipitation()
{
    return precipitation;
}

int
query_wind()
{
    return wind;
}

int
query_clouds()
{
    return clouds;
}

int
query_temperature()
{
    return temperature;
}

int
query_winddir()
{
    return winddir;
}


/*
 * q_wdir is simply the wind direction the wind is travelling. It 
 * will most likely be used in all kinds of weather terrains.
 *
 */
string
q_wdir()
{
    if (winddir = 1)
    {
	return "northwest";
    }

    if (winddir = 2)
    {
	return "southeast";
    }

    return "upwards";
}


//////////////////CASTLEWARD WEATHERSTRINGS///////////////////////
/*
 * Below are the weatherstrings for the weather incorporated into
 * the set_castleward() function.
 *
 */
string
q_cloud()
{

    if (clouds = 1)
    {
	return "there are no visible clouds in the sky.";
    }

    if (clouds = 2)
    {
	return "tome few clouds covers the sky.";
    }

    return "Some buggy clouds at the sky.";
}

string
q_prec()
{
    if (precipitation = 1)
    {
	return "Some raindrops falls from above, spashing at the ground.";
    }

    if (precipitation = 2)
    {
	return "";
    }

    return "Some buggy rain falls from the sky. contact a wizard.";
}

string
q_temp()
{
    if (temperature = 1)
    {
	return "The temperature is low, close to sub-zero.";
    }

    if (temperature = 2)
    {
	return "The temperature is low.";
    }

    return "The temperature is Buggy. contact a wizard.";
}


string
q_wind()
{
    if (wind = 1)
    {
	return "You feel a weak breeze from "+q_wdir()+" blowing at your face";
    }

    if (wind = 2)
    {
	return "You feel a weak breeze from "+q_wdir()+" blowing at your face";
    }

    if (wind = 3)
    {
	return "A strong breeze from "+q_wdir()+" blows at your face";
    }

    return "No wind blows here.\n";
}

