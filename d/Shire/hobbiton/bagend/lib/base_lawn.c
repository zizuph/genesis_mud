/*
 *	/d/Gondor/common/lib/area_room.c
 *	A standard file for outdoor rooms in Gondor
 *
 *	Copied from /d/Gondor/common/lib/field.c by Elessar.
 *
 *	Copyright (c) 1993 - 1997 by Rolf Braun, Henry Hardy,
 *	and Christian Markus
 *
 *	Modifications:
 *	Removed make_the_room(), replaced by create_area_room()
 *      Olorin, January 1995
 *	General revision, changed inheritance
 *	Olorin, January 1997
 *	Integrated changed descriptions from Zephram's version of the
 *	area_room file.
 *	Olorin and Zephram, February 1997
 *
 *      Ruthlessly stolen by Igneous for use in the Shire
 *      Made a few modifiactions, to fit Shires needs.
 *      Igneous, September 1997
 *
 *  Removed BSN() from file so the descriptions correspond to options screenwidth
 *  Added a \n in the return of long_desc().
 *  -- Finwe May 9, 2004
 */
#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include <ss_types.h>
#include "/d/Shire/sys/terrain.h"

inherit SHIRE_ROOM;
inherit HERB_SEARCH;

/*
 *      Prototypes:
 */
public int check_lightlevel();

/*
 *      Global variables:
 */
static int     areatype,    /*  0 = no type desc, 1 = Grass,    2 = Bushes,
                             *  3 = Trees,        4 = Farmland, 5 = Rocky,
                             *  6 = Snow,         7 = Forest,   8 = Road,
                             *  9 = Barren,      10 = Village, 11 = Path,
                             * 12 = Ruins,       13 = Marsh,   14 = Hills
                             * 15 = Shore,       16 = Beach,   17 = Woods
                             * Definitions found in ~Shire/sys/terrain.h
                             */
               forest_density;
static string  area = "central",    // eg "northern"
               areadesc = "field",  // eg "green, grassy field", "dense thicket"
               areaname,	        // eg "Anorien", "Lebennin", "Rohan"
               land = "Shire",      // "Shire"
               grass = "green",     // (1), (2), (3)
               extraline,           // additional room description
               treetype = "oak",    // (3), (7)
               water = "dark brackish";   // (11)
static string  forest,              // not used in the master
               mountain;           // not used in the master
function vbfc_extra;

void
set_vbfc_extra(function f)
{
    vbfc_extra = f;
}

void   set_areatype(int i)       { areatype = i; }
void   set_area(string str)      { area = str; }
void   set_areadesc(string str)  { areadesc = str; }
void   set_areaname(string str)  { areaname = str; }
void   set_extraline(string str) { extraline = str; }
void   set_land(string str)      { land = str; }

static string
short_desc()
{
    string  desc;

    switch (areatype)
    {
        case 0:
            desc = LANG_ADDART(areadesc)+" " + area + " " +
            areaname + " in " + land;
            break;
    }
    return desc;
}

string
describe_time(string time)
{
    string desc;

    switch (time)
    {
        case "night":
            desc = "Night time covers "+areaname+". ";
            switch (CLOCK->query_moon())
        {
           case "full":
               desc += "A full moon sheds some light across the land. ";
               break;
           case "waxing crescent":
           case "waxing gibbous":
           case "waning gibbous":
           case "waning crescent":
               desc += "The moon sheds a little light across the land. ";
               break;
           default:
               desc += "The sky is covered with dark clouds, and "+
               "not even the moon shines through. ";
               break;
        }
        break;
        case "afternoon":
            desc = "The light of day shines across " + areaname + "."+
            " It is afternoon. ";
            break;
        case "morning":
            desc = "The sun is on its way up in the morning sky "
            + "to the east. ";
            break;
        case "noon":
            desc = "The sun is almost at its peak on its way across "
            + "the sky. It is noon in " + areaname + ". ";
            break;
        case "evening":
            desc = "The sun is setting in the west, colouring the sky "
            + "golden red. ";
            break;
        case "early morning":
            desc = "The sun is rising in the east, casting long shadows "
            + "across "+areaname+". ";
            break;
        }
    return desc;
}

string
describe_war(string time)
{
    string desc;

    switch (time)
    {
        case "evening":
        case "night":
        case "early morning":
            desc = " Massive dark clouds cover the sky, making it "
            + "difficult to distinguish night and day. The clouds seem "
            + "to be coming from the east, where Mordor lies. You "
            + "suspect it is night now, as it is as dark as it can get. ";
            break;
        case "morning":
            desc = " A thick cover of clouds prevent the sun from "
            + "shining on the lands of "+land+", and it is almost as "
            + "dark as at night. However you gather that it is probably "
            + "morning, as it is getting a bit lighter than earlier. ";
            break;
        case "noon":
            desc = " A dark mass of clouds seems to be rolling in from "
            + "the east, covering the sky above "+land+". It is not much "
            + "lighter now than it usually is at night, but still you "
            + "suspect it is the middle of the day. ";
            break;
        case "afternoon":
            desc = " A thick mass of clouds covers the sky, making it "
            + "difficult to see far. You suspect that it is afternoon, "
            + "as it is getting a bit darker than earlier. ";
            break;
        }

    return desc;
}

public string
long_desc()
{
    string  time  = CLOCK->query_time_of_day(),
    desc = CAP(query_short()) + ". ";

    if (!(CLOCK->query_war()))
    {
        desc += describe_time(time);
    }
    else
    {
        desc += describe_war(time);
    }

    if (strlen(extraline))
        desc += extraline;

    if (functionp(vbfc_extra))
        desc += " " + vbfc_extra();
    return (desc + "\n");

}

void
add_herbs()
{
    int seed;

    seed = file_size(file_name(calling_object()) + ".c");
    add_std_herbs(0, seed);
}

void
create_area_room()
{
}

nomask void
create_shire_room()
{
    remove_prop(ROOM_I_INSIDE);
    add_prop(ROOM_I_LIGHT, check_lightlevel);

    create_area_room();

    set_short(short_desc());   // It is not necessary to use a VBFC here!
    set_long(long_desc);
    add_herbs();
}

public int
check_lightlevel()
{
    switch (tod())
    {
    case "night":
   return 1;
   break;
    case "early morning":
    case "evening":
   return 2;
   break;
    case "morning":
    case "noon":
    case "afternoon":
   return 3;
   break;
    default:
   return 1;
    }
}

public void
init()
{
    ::init();
}
