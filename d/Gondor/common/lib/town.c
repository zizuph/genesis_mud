/*
 *  Standard file for Edoras- Capitol of Rohan
 *  v2.1 By Hamurabbi (e90jp1@hh.se) Dec 1991 - Jan 1992
 *  Time-command for mortals added by Elessar 27/3-92 + some typos :)
 *
 *  Some minor modifications, Olorin, March 1995
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static  string  hillside,
                geoextra,
                peopextra,
                extraline,
                ro,
                hei,
                sky;
static  int     height,
                people,
                road,
                density;

void    set_hillside(string str) { hillside = str; }
void    set_extraline(string str) { extraline = str; }
void    set_height(int n) { height = n; }
void    set_people(int n) { people = n; }
void    set_road(int n) { road = n; }
void    set_density(int n) { density = n; }

void
make_the_room()
{
    switch (road)
    {
        case 0: ro = "in Edoras";                break;
        case 1: ro = "on Kingsroad";             break;
        case 2: ro = "on the Golden Staircase";  break;
        case 3: ro = "on a square";              break;
        default: ro = "in Edoras";               break;
    }

    switch (height)
    {
        case 1: hei = "almost at the bottom of";  break;
        case 2: hei = "about one third up";       break;
        case 3: hei = "about one third up";       break;
        case 4: hei = "some two thirds up";       break;
        case 5: hei = "at the crown of";          break;
        default: hei = "somewhere";               break;
    }

    set_short(ro+" on the "+hillside+" side of the hill");
    set_long("@@describe");

    switch (hillside)
    {
        case "north":
            add_item(({"view","mountains","plains","plain"}),
                BSN("To the north you see the grasscovered plains of "
              + "Rohan spread out towards the horizon. To the south the "
              + "hill on which Edoras is situated continues upwards and "
              + "downwards. Behind the hill you see the mighty White "
              + "Mountains stretch from west towards east."));
            break;
        case "east":
	    add_item(({"view","mountains","plains","plain"}),
                BSN("To the north you see the grasscovered plains of "
              + "Rohan spread out towards the horizon. To the east the "
              + "plains continues.To the south is the mighty  White "
              + "Mountains and they continue towards the east as far as "
              + "you can see.")); 
            break;
        case "south":
            add_item(({"view","mountains","plains","plain"}),
                BSN("To the south the mighty White Mountains stretch out "
              + "from west towards east. A bit to the southeast the high "
              + "mountain peak Irensaga raise towards the sky. To the "
              + "north the hill on which Edoras is situated continues "
              + "upwards and downwards. To the east and west the "
              + "grass-covered plains of Rohan extend towards the horizon."));
            break;
        case "west":
            add_item(({"view","mountains","plains","plain"}),
                BSN("To the north you see the grass-covered plains of "
              + "Rohan spread out towards the horizon. To the west the "
              + "plains continues. To the south are the mighty White "
              + "Mountains and they continue towards the west as far as "
              + "you can see.")); 
            break;
        default:
            break;
    }
}

string
describe(string str) 
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day(),
            long_descf,
            dens_desc = "";

    if (strlen(str))
        return "";

    long_descf = "You are standing "+ro+". You are on the "+hillside
      + " side, "+hei+" the hill.";
    long_descf += " It is "+time+" in Rohan.";

    sky = clock->query_moon();

    switch (time)
    {
        case "night":
            dens_desc = " All is quiet in Edoras. All people are at "
              + "home, but a lonesome guard is walking by. The lights "
              + "are out in all the houses.";
            switch (sky)
            {
                case "dark":
                    long_descf += " You get an uneasy feeling when you "
                      + "look at the sky. The dark sky is full of clouds "
                      + "and there is a great chill in the air.";
                    break;
                case "full":
	            long_descf += " The dark sky above you is full of "
                      + "bright stars and the fullmoon shines through "
                      + "the clear air.";
                    break;
                default:
	            long_descf += " The dark sky above you is full of "
                      + "bright stars and the air is clear.";
                    break;
            }
            break;
        case "early morning":
            dens_desc = " Some people have awakened but you do not see "
              + "many outside yet. From some of the houses a nice aroma "
              + "of newly baked bread tickles your nostrils.";
            switch (sky)
            {
                case "dark":
	            long_descf += " The sun has barely made it over the "
                      + "eastern horizon and can be seen through the heavy "
                      + "clouds that fill the sky. The air is thick and "
                      + "an uneasy feeling fills you with apprehension.";
                    break;
                default:
	            long_descf += " The sun has barely made it over the "
                      + "eastern horizon. The air is fresh and new.";
                    break;
            }
            break;
        case "morning":
            dens_desc += " People are all around you, moving around "
              + "on their daily business. Children are playing in the "
              + "gutter and a dog is running by.";
            long_descf += " The sun has worked its way up the clear sky. "
              + "Now is a perfect time for travelling, not too warm and "
              + "not too cold.";
            break;
        case "noon":
            dens_desc += " As it is the middle of the day people are "
              + "having lunch in their homes, and only a few can be "
              + "seen on the streets.";
            switch (sky)
            {
                case "dark":
	            long_descf += " Through the clouds the sun can be "
                      + "seen shining down from right above your head. "
                      + "The quietness of the noon has settled over "
                      + "everything.";
                    break;
                default:
	            long_descf += " The sun shines down from right above "
                      + "your head. The quietness of the noon has settled "
                      + "over everything.";
                    break;
            }
            break;
        case "afternoon":
            dens_desc += " People are all around you, moving around "
              + "on their daily business. Children are playing in the "
              + "gutter and a dog is running by.";
            switch (sky)
            {
                case "dark":
	            long_descf += " Through the clouds the sun can be "
	              + "seen moving towards the west, slowly descending "
                      + "on its way over the sky. The air is thick.";
                    break;
                default:
	            long_descf += " The sun is moving towards the west, "
                      + "slowly descending on its way over the sky. The "
                      + "air is warm and fresh.";
                    break;
            }
            break;
        case "evening":
            dens_desc += " People are finishing their business and the "
             + "shopkeepers are closing up for the day. Lights are "
             + "beginning to shine from the windows.";
            switch (sky)
            {
                case "dark":
	            long_descf += " The sun is setting behind the thick "
                      + "clouds as darkness is spreading.";
                    break;
                default:
                    long_descf += " The sun paints the horizon to the "
                      + "west with firelike colours.";
                    break;
            }
            break;
        default:
            long_descf += " You do not know the time!!!\n";
            break;
    }

    switch (density)
    {
        case 1:
            long_descf += " There are not so many houses around you. "
              + "This area of Edoras is mainly used for cultivating and "
              + "for paddocks." + dens_desc;
            break;
        case 2:
            long_descf += " This is a residental area of Edoras. There "
              + "are houses all around you." + dens_desc;
            break;
        case 3:
	    long_descf += " This is an area of Edoras mainly used for "
              + "shops and stores." + dens_desc;
            break;
        case 4:
	    long_descf += " This is the central area of Edoras, next to "
              + "the golden hall Meduseld. Normally, only members of the "
              + "royal household and nobles of the mark are admitted here.";
            break;
        default:
            break;
    }

    if (strlen(extraline))
        long_descf += " " + extraline;
    return BSN(long_descf);
}
