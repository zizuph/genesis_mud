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
public int     check_lightlevel();
public int     do_climb(string str);

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
void   set_forest_density(int i) { forest_density = i; }
void   set_vegetation_density(int i) { forest_density = i; }

void   set_area(string str)      { area = str; }
void   set_areadesc(string str)  { areadesc = str; }
void   set_areaname(string str)  { areaname = str; }
void   set_land(string str)      { land = str; }
void   set_grass(string str)     { grass = str; }
void   set_extraline(string str) { extraline = str; }
void   set_treetype(string str)  { treetype = str; }
void   set_forest(string str)    { forest = str; }
void   set_water(string str)     { water = str; }
void   set_mountain(string str)  { mountain = str; }

static string
short_desc()
{
    string  desc;

    switch (areatype)
    {
    case AREATYPE_GRASS:
        if (!item_id("field"))
            add_item("field","The field is covered by "+grass
                + " grass all over.\n");
        if (!item_id("grass"))
            add_item("grass","The "+grass+" grass grows all "
                + "over the field.\n");
        desc = "a grassy "+areadesc+" "+area+" "
        + areaname+" in "+land;
        break;
    case AREATYPE_BUSHES:
        if (!item_id(areadesc))
            add_item(areadesc, "On the green "+areadesc+" "+grass+
                " grass grows, along with some bushes here and there.\n");
        if (!item_id("bushes"))
            add_item("bushes", "Some bushes growing here on the "
                + areadesc+".\n");
        desc = "a bushy "+areadesc+ " "+area
        + " "+areaname+" in "+land;
        break;
    case AREATYPE_TREES:
        if (!item_id(areadesc))
            add_item(areadesc, "The "+areadesc+" is overgrown with "
                + grass+" grass, and some trees also stand here.\n");
        if (!item_id("trees"))
            add_item("trees", "A few "+treetype+" trees also grow here.\n");
        desc = LANG_ADDART(areadesc)+" with some trees "+area
        + " "+areaname+" in "+land;
        break;
    case AREATYPE_FARMLAND:
        if (!item_id("field"))
            add_item("field", 
            "You see a field used for agriculture by the people of "
            + land+", as it is covered by furrows and plough-marks "
            + "here and there.");
        if (!item_id("furrow"))
            add_item("furrow",
                "The furrows clearly indicate that this is farmland.\n");
        desc = "an agricultural "+areadesc+" "+area
        + " "+areaname+" in "+land;
        break;
    case AREATYPE_ROCKY:
        if (!item_id("ground"))
            add_item("ground", "The ground is quite rocky and barren.\n");
        if (!item_id("grass"))
            add_item(({"grass","trees","bushes","herbs"}), "There is no "
                + "green growth here, the ground is too rocky and hard.\n");
        desc = "a rocky "+areadesc+ " "+area+" "
        + areaname+" in "+land;
        break;
    case AREATYPE_SNOW:
        if (!item_id("ground"))
            add_item("ground","The ground is covered with snow here.\n");
        if (!item_id("snow"))
            add_item("snow","The snow is white and cold.\n");
        desc = "A snowy "+areadesc+ " "+area+" "
        + areaname+" in "+land;
        break;

    case AREATYPE_FOREST:
        if (!item_id("ground"))
            add_item("ground", "There are dry leaves and moss on the "
                + "forest floor.\n");
        if (!item_id("moss"))
            add_item("moss", "It is soft green moss, a bit yellow in "
                + "patches.\n");
        if (!item_id("leaves"))
            add_item("leaves", "They have fallen down from the "+treetype
                + " trees.\n");
        if (!item_id("trees"))
            add_item(({treetype, treetype+" trees", "trees"}),
                "The "+treetype+" trees that grow here make up most "
                + "of the forest.\n");
        desc = LANG_ADDART(areadesc)+" in a forest "+area
        + " "+areaname+" in "+land;
        break;


    case AREATYPE_WOODS:
        if (!item_id("ground"))
            add_item("ground", "Grey oak leaves cover the floor of "
                + "the ancient woods.\n");
        if (!item_id("leaves"))
            add_item("leaves", "They have fallen down from the "+treetype
                + " trees and completely cover the ground.\n");
        if (!item_id("trees"))
            add_item(({treetype, treetype+" trees", "trees"}),
                "The "+treetype+" trees that grow here make up most "
                + "of the forest.\n");
        desc = LANG_ADDART(areadesc)+" in an ancient woods "+area
        + " "+areaname+" in "+land;
        break;

    case AREATYPE_ROAD:
        if (!item_id("road"))
            add_item("road", "You are on a dusty road in "+land
                + ". You are not sure where it leads.\n");
        if (!item_id("ground"))
            add_item("ground","You see a dusty road.\n");
        desc = "a road across "+LANG_ADDART(areadesc)+" "
        + area+" "+areaname+" in "+land;
        break;
   case AREATYPE_BARREN:
        if (!item_id("ground"))
            add_item("ground", "The ground is quite barren, so there "
                + "is not much that grows here.\n");
        desc = "a barren "+areadesc+" "+area+" "
        + areaname+" in "+land;
        break;
   case AREATYPE_VILLAGE:
        if (!item_id("road"))
            add_item("road", "You're on a dusty road passing through "+
                "the "+areadesc+" of "+areaname+".\n");
        desc = "a road passing through the "+areadesc+" of "+
        areaname +" in " + land;
        break;

   case AREATYPE_PATH:
        if (!item_id("path"))
            add_item("path", "You are on a small path, uncertain "+
                "whereit will take you.\n");
        desc = "a path passing through "+LANG_ADDART(areadesc)+
        " " + area + " " + areaname + " in " + land;
        break;

   case AREATYPE_RUINS:
    if ( !item_id("ground") && !item_id("ruin") &&
        !item_id("stone") )
        add_item( ({ "ground", "ruin", "ruins", "stone",
        "stones", }),
            "Small " + treetype + " trees are growing " +
        "from cracks in the old ruins. Once works of " +
        "craft were builded here, but they crumbled " +
        "long ago. Now only tumbled, half-covered " +
        "stones offer mute testimony to their builders.");
    desc = "some old ruins in " + LANG_ADDART(areadesc) +
    " " + area + " " + areaname +
    " in " + land;
    break;
    case AREATYPE_MARSH:
   if ( !item_id("ground") && !item_id("swamp") &&
     !item_id("water") && !item_id("marsh") )
       add_item( ({ "ground", "swamp", "water", "marsh", }),
        "Some " + treetype + " trees still poke " +
        "their heads above the " + water + " water.");
   desc = "an overgrown swamp in " + LANG_ADDART(areadesc) +
   " of the " + area + " " + areaname +
   " in " + land;
   break;
    case AREATYPE_HILLS:
   if ( !item_id("ground") && !item_id("hill") &&
     !item_id("hills") && !item_id("height") &&
     !item_id("heights") )
       add_item( ({ "ground", "hill", "hills", "height",
      "heights", }),
         "A few sparse " + treetype + " trees struggle up " +
         "the lower slopes.\n");
   desc = "some hills above " + LANG_ADDART(areadesc) +
   " " + area + " " + areaname +
   " in " + land;
   break;
    default:
   desc = LANG_ADDART(areadesc)+" "+area+" "
   + areaname+" in "+land;
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
        // Palmer removed extra space 12/07/2003
        desc += extraline;
        //desc += (" " + extraline);
    if (functionp(vbfc_extra))
        desc += " " + vbfc_extra();
    return (desc + "\n");

/*
    if (strlen(extraline))
        desc += extraline;
    if (functionp(vbfc_extra))
        desc += vbfc_extra();
    return (desc);
*/
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

int
query_road()
{
    if (areatype == AREATYPE_ROAD || areatype == AREATYPE_VILLAGE)
   return 1;
    return 0;
}

public void
init()
{
    ::init();
    if ((areatype == AREATYPE_TREES) || 
      (areatype == AREATYPE_FOREST) || 
      item_id("tree"))
   add_action(do_climb, "climb");
}

public int
do_climb(string str)
{
    if (!strlen(str) ||
      (str != "tree" && str != "trees" && str != treetype && 
   str != treetype+" tree" && str != treetype+" trees"))
   NF("Climb what?\n");
    else
   NFN("You cannot climb the "+str+", as even the lowest "
     + "branches are too high.");
    return 0;
}


/*
 * Function name: test_track
 * Description:   compare player's tracking skill to forest density
 * Returns:       add_exit flag 0/1
 */
public int
test_track()
{
    if (TP->query_skill(SS_TRACKING) >= random(forest_density))
    {
   write("You succeed in following the path.\n");
   return 0;
    }
    else
    {
   write("You quickly lose track of the path, and return to where you were.\n");
   say(QCTNAME(TP)+" lost track of the path, and returned here.\n", TP);
   return 1;
    }
}

/*
 * Function name: test_loc
 * Description:   compare player's location sense to forest density
 * Returns:       add_exit flag 0/1
 */
public int
test_loc()
{
    if (TP->query_skill(SS_LOC_SENSE) >= random(forest_density))
   return 0;
    else
    {
   write("You feel disoriented as to what is the correct direction, so "
     + "you stop in fear of getting lost.\n");
   say(QCTNAME(TP)+" cannot decide which direction to go.\n");
   return 1;
    }
}
