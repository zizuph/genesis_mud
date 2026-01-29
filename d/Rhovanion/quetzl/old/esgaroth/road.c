#pragma strict_types
 
#include "esg_defs.h"
 
inherit BASE_ROOM;
 
#include <stdproperties.h>
#include <macros.h>
 
static mapping cloud_map = ([]);
 
public string
moon_stars(string which)
{
    string tim;
    tim = query_time_of_day();
    if (tim != "night" && tim != "midnight")
        return "You realize that the " + which + " won't be visible until " +
            "night.\n";
 
    tim = query_weather();
    if (tim != "clear")
        return "The " + (which == "moon" ? "moon is " : "stars are ") +
            "obscured by clouds.\n";
    if (which == "stars")
        return "The stars wheel above you in the grand majesty of the sky.\n";
    return "You stare up at the " + CLOCK->query_moon() + " moon in wonder.\n";
}
 
public string
sky_desc()
{
    string tim, wet;
    tim = query_time_of_day();
    wet = query_weather();
    if (tim == "night" || tim == "midnight")
    {
        switch(wet)
        {
            case "clear" :
                return "The night sky looms above you, dark " +
                "and eternal.\n";
            case "cloudy" :
                return "The night sky is dark, filled with clouds.\n";
            case "raining" :
                return "The night sky is dark, filled with clouds. You " +
                "feel rain on your face as you look.\n";
         }
         return "The sky is above you.\n";
    }
 
    switch(wet)
    {
        case "clear" :
            return "The sky is clear and blue.\n";
        case "cloudy" :
            return "Clouds fill the sky.\n";
        case "raining" :
            return "Clouds fill the sky, and rain falls over the city.\n";
    }
}
 
public string
sun_desc()
{
    string tim, wet;
    tim = query_time_of_day();
    wet = query_weather();
 
    switch (tim)
    {
        case "night" :
            return "The sun is no longer above the horizon.\n";
        case "early morning" :
            switch (wet)
            {
                case "clear" :
                    return "Dawn has come brilliantly to Esgaroth, and the " +
                    "sun shines over the city from a clear blue sky.\n";
                case "cloudy" :
                    return "It is hard to find the sun through the clouds, " +
                    "but you manage to pick it out as a bright silver spot " +
                    "among the grey.\n";
                case "raining" :
                    return "You look up into the sky in a vain search for " +
                    "the sun and find only rain.\n";
            }
        case "morning" :
        case "noon" :
        case "afternoon" :
            switch (wet)
            {
                case "clear" :
                    return "You look up at the sun, but quickly look away " +
                    "before you are blinded by its light.\n";
                case "cloudy" :
                    if (this_player()->query_prop(LIVE_I_UNDEAD))
                        return "The cursed sun is thankfully hidden from " +
                        "view by the clouds.\n";
                    else
                        return "The sun is hidden from view by the " +
                        "clouds.\n";
                case "raining" :
                    return "Rain fills the sky, and you see no glimpse of " +
                    "the sun.\n";
            }
        case "evening" :
            switch (wet)
            {
                case "clear" :
                    return "The sun is sinking down to the horizon, casting " +
                    "golden rays across the earth.\n";
                case "cloudy" :
                    return "The sun has sunk below the lowest clouds, " +
                    "turning their undersides pink with the light.\n";
                case "raining" :
                    return "The approach of nightfall only increases the " +
                    "darkness caused by the rain.\n";
            }
 
    }
}
 
static string
cloud_face()
{
    string guild;
    string *descs = ({ "your mother", "your father", "a dragon",
        "a sailing ship", "a winged horse", "a bear", "one of the " +
        "trees of Mirkwood", "a bridge", "a castle", "a human",
        "a goblin", "an elf", "a dwarf", "a hobbit", "a gnome", });
    int i;
 
    if (cloud_map[guild = this_player()->query_guild_name_occ()])
        descs += cloud_map[guild];
    if (cloud_map[guild = this_player()->query_guild_name_lay()])
        descs += cloud_map[guild];
    if (cloud_map[guild = this_player()->query_gulid_name_race()])
        descs += cloud_map[guild];
    i = sizeof(descs);
    return descs[random(i)];
}
 
public string
cloud_desc()
{
    if (query_weather() == "clear")
        return "You see no clouds in the sky.\n";
    if (query_time_of_day() == "night")
        return "It is too dark to make anything out in the clouds.\n";
    return "You look up into the clouds and spot one that looks like " +
        cloud_face() + ".\n";
}
 
public void
initialize_road()
{
    remove_prop(ROOM_I_INSIDE);
    set_vary_func("time", query_time_of_day);
    set_vary_func("weather", query_weather);
 
    add_item("moon", "@@moon_stars|moon@@");
    add_item("stars", "@@moon_stars|stars@@");
    add_item(({ "sky", "overhead" }), "@@sky_desc@@");
    add_item("sun", "@@sun_desc@@");
    add_item(({ "clouds", "cloud" }), "@@cloud_desc@@");
 
    add_item(({ "street", "streets", "road", "roads", "boardwalk" }),
        "The streets of Esgaroth are made of wood garnered from " +
        "Mirkwood forest long ago, before it was inhabited by evil.\n");
}
