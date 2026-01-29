/*
 *	/d/Gondor/common/lib/area_room.c
 *	A standard file for outdoor rooms in Gondor
 *
 *	Copied from /d/Gondor/common/lib/field.c by Elessar.
 *
 *	Copyright (c) 1993 - 1997 by Rolf Braun, Henry Hardy, 
 *	and Christian Markus  
 *
 *  Modifications:
 *  Removed make_the_room(), replaced by create_area_room()
 *      Olorin, January 1995
 *  General revision, changed inheritance
 *      Olorin, January 1997
 *  Integrated changed descriptions from Zephram's version of the
 *  area_room file. 
 *      Olorin and Zephram, February 1997
 *  Removed BSN() from file
 *      Finwe, August 2005
 *  Fixed a space after the day description
 *      Toby, June 18, 2008
 *  Removed the extra space before extraline
 *  General cleanup
 *  Added add_items for sun and moon 
 *      Alto, June 24, 2017
 *
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/sys/sunlight.h"

/*
 *      Prototypes:
 */
public int      check_lightlevel();
public int      do_climb(string str);
public string   sun_moon_desc();
public string   sun_add_item();
public string   moon_add_item();

/*
 *      Global variables:
 */
static int     areatype,   /* 0 = no type desc, 1 = Grass, 2 = Bushes,
                            * 3 = Trees, 4 = Farmland, 5 = Rocky,
                            * 6 = Snow, 7 = Forest, 8 = Road, 9 = Barren
                            * 10 = Ruins, 11 = Marsh, 12 = Hills
                            * Definitions to be found in /d/Gondor/defs.h */
               forest_density;
static string  area = "central",    // eg "northern"
               areadesc = "field",  // eg "green, grassy field"
               areaname,            // eg "Anorien", "Lebennin", "Rohan"
               land = "Gondor",     // "Gondor"
               grass = "green",     // (1), (2), (3)
               extraline,           // additional room description
               treetype = "oak",    // (3), (7)
               water = "dark brackish";	// (11)
static string  forest,              // not used in the master
               mountain;            // not used in the master
function vbfc_extra;

void
set_vbfc_extra(function f)
{
    vbfc_extra = f;
}

void   set_areatype(int i)       { areatype = i; }
void   set_forest_density(int i) { forest_density = i; }
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
	    add_item("field","The field is covered by "+ grass + 
	    " grass all over.\n");
	if (!item_id("grass"))
	    add_item("grass","The "+ grass +" grass grows all " + 
	    "over the field.\n");
	desc = "a grassy "+ areadesc +" in the "+ area +" parts of " + 
	    areaname +" in "+ land;
	break;
    case AREATYPE_BUSHES:
	if (!item_id(areadesc))
	    add_item(areadesc, "On the green "+ areadesc +" "+ grass +
		     " grass grows, along with some bushes here and there.\n");
	if (!item_id("bushes"))
	    add_item("bushes", "Some bushes growing here on the " + 
	        areadesc +".\n");
	desc = "a bushy "+ areadesc + " in the "+ area + " parts of " + 
	    areaname +" in "+ land;
	break;
    case AREATYPE_TREES:
	if (!item_id(areadesc))
	    add_item(areadesc, "The "+ areadesc +" is overgrown with " + 
	        grass + " grass, and some trees also stand here.\n");
	if (!item_id("trees"))
	    add_item("trees", "A few "+ treetype +" trees also grow here.\n");
	desc = LANG_ADDART(areadesc) +" with some trees in the "+ area + 
	    " parts of "+ areaname +" in "+ land;
	break;
    case AREATYPE_FARMLAND:
	if (!item_id("field"))
            add_item("field", 
                "You see a field used for agriculture by the people of " + 
                land +", as it is covered by furrows and plough-marks " + 
                "here and there.");
	if (!item_id("furrow"))
            add_item("furrow",
		     "The furrows clearly indicate that this is farmland.\n");
	desc = "an agricultural "+ areadesc +" in the "+ area + " parts of " + 
	    areaname+" in "+ land;
	break;
    case AREATYPE_ROCKY:
	if (!item_id("ground"))
	    add_item("ground", "The ground is quite rocky and barren.\n");
	if (!item_id("grass"))
	    add_item(({"grass","trees","bushes","herbs"}), "There is no " + 
	        "green growth here, the ground is too rocky and hard.\n");
	desc = "a rocky "+ areadesc + " in the "+ area +" parts of " + 
	    areaname + " in "+ land;
	break;
    case AREATYPE_SNOW:
	if (!item_id("ground"))
	    add_item("ground","The ground is covered with snow here.\n");
	if (!item_id("snow"))
	    add_item("snow","The snow is white and cold.\n");
	desc = "A snowy "+ areadesc + " in the "+ area +" parts of " + 
	    areaname + " in " + land;
	break;
    case AREATYPE_FOREST:
	if (!item_id("ground"))
	    add_item("ground", "There are dry leaves and moss on the " + 
	        "forest floor.\n");
	if (!item_id("moss"))
	    add_item("moss", "It is soft green moss, a bit yellow in " + 
	        "patches.\n");
	if (!item_id("leaves"))
	    add_item("leaves", "They have fallen down from the "+ treetype + 
	        " trees.\n");
	if (!item_id("trees"))
	    add_item(({treetype, treetype+" trees", "trees"}),
		     "The "+ treetype +" trees that grow here make up the " + 
		     "most of the forest.\n");
	desc = LANG_ADDART(areadesc)+" in a forest in the "+ area + 
	    " parts of "+ areaname + " in " + land;
	break;
    case AREATYPE_ROAD:
	if (!item_id("road"))
	    add_item("road", "You are on a dusty road in "+ land + 
	        ". You are not sure where it leads.\n");
	if (!item_id("ground"))
	    add_item("ground","You see a dusty road.\n");
	desc = "a road across " + LANG_ADDART(areadesc) + " in the " + area + 
	    " parts of "+ areaname +" in "+ land;
	break;
    case AREATYPE_BARREN:
	if (!item_id("ground"))
	    add_item("ground", "The ground is quite barren, so there " + 
	        "is not much that grows here.\n");
	desc = "a barren "+ areadesc +" in the "+ area +" parts of " + 
	    areaname + " in " + land;
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
	    " in the " + area + " parts of " + areaname +
	    " in " + land;
	break;
    case AREATYPE_MARSH:
	if ( !item_id("ground") && !item_id("swamp") &&
	     !item_id("water") && !item_id("marsh") )
	    add_item( ({ "ground", "swamp", "water", "marsh", }), 
		      "Some " + treetype + " trees still poke " +
			  "their heads above the " + water + " water.");
	desc = "an overgrown swamp in " + LANG_ADDART(areadesc) +
	    " of the " + area + " parts of " + areaname + 
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
	    " in the " + area + " parts of " + areaname + 
	    " in " + land;
	break;
    default:
	desc = LANG_ADDART(areadesc) + " in the "+ area +" parts of " + 
	    areaname +" in "+ land;
	break;
    }
    return desc;
}

public string
long_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day(),
            desc  = CAP(query_short()) + ".";

    if (!(clock->query_war()))
    {
        switch (time)
        {
        case "night":
            desc += " A sprinkling of Elbereth's stars can be seen " +
		"twinkling high above Middle-Earth. It is night in " +
		areaname + ".";
            switch (clock->query_moon())
            {
            case "full":
                desc += " The full moon, fair Ithil, bathes the " +
		    areadesc + " in liquid silver light."; 
                break;
            case "waxing crescent":
               desc += " The crescent moon illuminates the " + 
		   areadesc + " faintly.";
                break;
            case "waxing gibbous":
		desc += " The moon, now approaching full, casts " +
		    "a silvery light."; 
		break;
            case "waning gibbous":
		desc += " The moon, now past full, still casts a " +
		    "serviceable white light."; 
		break;
            case "waning crescent":
                desc += " The moon tilts its slender upturned " +
		    "horns over the gloomy landscape."; 
                break;
            default:
		desc += " The sky is obscured by dark clouds.";
                break;
            }
            break;
        case "afternoon":
            desc += " Daylight shines across " + areaname + "." +
                " It is afternoon.";
            break;
        case "morning":
            desc += " The sun is on its way up in the morning sky " + 
                "to the east.";
            break;
        case "noon":
            desc += " The sun is almost at its peak on its way " +
                "across the sky. It is noon in " + areaname + ".";
            break;
        case "evening":
            desc += " The sun is setting in the west, colouring the " + 
                "sky golden red.";
            break;
        case "early morning":
            desc += " The sun is rising in the east, casting long " + 
                "shadows across "+ areaname +".";
            break;
        }
    }
    else 
    {
        switch (time)
        {
        case "evening":
        case "night":
        case "early morning":
            desc += " Massive dark clouds cover the sky, making it " + 
                "difficult to distinguish night and day. The clouds seem " + 
                "to be coming from the east, where Mordor lies. You " + 
                "suspect it is night now, as it is as dark as it can get.";
            break;
        case "morning":
            desc += " A thick cover of clouds prevent the sun from " + 
                "shining on the lands of " + land + ", and it is almost " + 
                "as dark as at night. However you gather that it is " +
                "probably morning, as it is getting a bit lighter " +
                "than earlier.";
            break;
        case "noon":
            desc += " A dark mass of clouds seems to be rolling in from " + 
                "the east, covering the sky above " + land + 
                ". It is not much lighter now than it usually is at " +
                "night, but still you suspect it is the middle of the day.";
            break;
        case "afternoon":
            desc += " A thick mass of clouds covers the sky, making it " + 
                "difficult to see far. You suspect that it is afternoon, " + 
                "as it is getting a bit darker than earlier.";
            break;
        }
    }
    desc += " ";

    if (strlen(extraline))
        desc += (extraline + "\n");  /* removed " " before extraline */
    if (functionp(vbfc_extra))
        desc += vbfc_extra() + "\n";
    return (desc);
}

/*
 * Function name: sun_moon_desc
 * Description:   time sensitive descriptions of sun and moon
 * Returns:       string to be used in add_item description
 */
public string
sun_moon_desc()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day(),
            sun,
            moon;

    if (!(clock->query_war()))
    {
        switch (time)
        {
        case "night":
            switch (clock->query_moon())
            {
            case "full":
                moon = "Bright silver light from the full moon " +
                    "shines upon the " + areadesc + ".\n"; 
                return moon;
            case "waxing crescent":
               moon = "The pale moon forms a graceful sickle " + 
                "that tilts in the sky above the " + areadesc + ".\n";
                return moon;
            case "waxing gibbous":
                moon = "Although it has yet to reveal the fullness " + 
                "of its pale face, the gibbous moon nonetheless " + 
                "gleams brightly in the sky.\n"; 
                return moon;
            case "waning gibbous":
                moon = "Having revealed its full face in recent " + 
                "days, the moon now wanes as it travels across the " + 
                "sky.\n"; 
                return moon;
            case "waning crescent":
                moon = "The waning moon is a graceful crescent that " +
                "adorns the night sky with a sliver of light.\n"; 
                break;
            default:
                moon = "The moon has slipped behind passing clouds " + 
                "and cannot be directly seen from here.\n";
                return moon;
            }
        case "afternoon":
            sun = "The afternoon sun warms " + areaname + 
            " as it descends westward from its summit in the sky.\n";
            return sun;
        case "morning":
            sun = "The sun is a magnificant ball of warm red light " +
            "that heralds the arrival of a new day.\n";
            return sun;
        case "noon":
            sun = "The sun has reached its highest point, shining " +
            "magestically over " + areaname + ".\n";
            return sun;
        case "evening":
            sun = "In the western sky, the sun is sinking into " +
            "the horizon, relinquishing the sky to the coming night.\n";
            return sun;
        case "early morning":
            sun = "Dim light glows upon the eastern horizon as " +
            "the sun awakes to claim the sky above " + areaname + 
            " once more.\n";
            return sun;
        }
    }
}

/*
 * Function name: sun_add_item
 * Description:   change sun description at different times
 * Returns:       add_item string
 */
public string   
sun_add_item()
{
    int checksun = check_lightlevel();
    string sundesc;
    
    if (checksun == 1)
    {
        sundesc = "The sun is rising over distant lands and cannot " +
        "presently be seen from " + areaname + " where it is night.\n";
        return sundesc;
    }
    else
    {
        sundesc = sun_moon_desc();
        return sundesc;
    }
}

/*
 * Function name: moon_add_item
 * Description:   change moon description at different times
 * Returns:       add_item string
 */
public string   
moon_add_item()
{
    int checkmoon = check_lightlevel();
    string moondesc;
    
    if (checkmoon == 1)
    {
        moondesc = sun_moon_desc();
        return moondesc;
    }
    else
    {
        moondesc = "The moon sails the skies of distant lands and " +
        "cannot be seen from " + areaname + " where it is daytime.\n";
        return moondesc;
    }
}

void
create_area_room()
{
    ::create_gondor();
}

nomask void
create_gondor()
{
    remove_prop(ROOM_I_INSIDE);
    add_prop(ROOM_I_LIGHT, check_lightlevel);

    create_area_room();
    
    
    set_short(short_desc());
    set_long(long_desc);
    add_item(({"sun"}), sun_add_item);
    add_item(({"moon"}), moon_add_item);
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
    if (areatype == AREATYPE_ROAD) 
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
          + "branches sturdy enough to bear your weight are too high.");
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
        write("You quickly lose track of the path, and return to where " + 
            "you were.\n");
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
        write("You feel disoriented as to what is the correct direction, " + 
            "so you stop in fear of getting lost.\n");
        say(QCTNAME(TP)+" cannot decide which direction to go.\n");
        return 1;
    }
}
