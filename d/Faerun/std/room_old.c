/*
 * Faerun's standard outdoor room. This file should be inherited by all 
 * rooms within Faerun!
 *
 *  Copyright (C)  Chad Richardson,   Feb 97
 *  -Igneous-
 *
 *  Updated for Faerun by Finwe, March 2006
 */


#include "/d/Faerun/sys/mudtime.h";
#include "/d/Faerun/sys/sunlight.h"
#include "/d/Faerun/defs.h"
//#include "/d/Faerun/herbs/herb_list.h"

inherit "/std/room";
inherit "/d/Faerun/std/room_tell";
inherit "/d/Faerun/std/search";
inherit "/d/Faerun/std/cmd_parse";
inherit HERB_SEARCH;

/*
 * Fix to get rid of the obnoxius 'What ?' when we try to walk in a nonexistant
 * direction. These are the default direction commands in the prefferred order.
 */
#define DEF_DIRS ({ "north", "east", "south", "west", \
    "northeast", "northwest", "southeast", "southwest", "up", "down" })

/*
 * The following two sort functions are used to sort the exits in
 * a specific, unified format.  Check the DEF_DIRS define for the
 * sorted order of the standard exits.  All other exits will be
 * added in AFTER those 10 in alphabetical order.
 * And yes, I know it looks like an ugly hack, but it DOES work. ;)
 */
static nomask int
sort_alpha(string one, string two)
{
    if (one > two)
		return 1;
    if (one < two)
		return -1;
    return 0;
}

static nomask int
resort_exits(string one, string two)
{
    int a, b;

    a = member_array(one, DEF_DIRS);
    b = member_array(two, DEF_DIRS);

    if (a >= 0 && b == -1)
		return -1;
    if (a == -1 && b >= 0 )
		return 1;
    if (a == b)
		return sort_alpha(one, two);
    if (a > b)
		return 1;
    if (a < b)
		return -1;
    return 0;
}

/* This is masked to sort the exits. */
public string *
query_obvious_exits(void)
{
    string *obv_exits = ::query_obvious_exits();

    if (obv_exits)
		obv_exits = sort_array(obv_exits, resort_exits);

    return obv_exits;
}

// Added so you can add extra descriptions to the room.
static string extraline = "";

//  Prototypes
nomask public int query_sunlight();
void   set_extraline(string str) { extraline = str; }
function vbfc_extra;

void
set_vbfc_extra(function f)
{
    vbfc_extra = f;
}


/*
 * Function name : create_faerun_room
 * Description   : This is the create function to be used when creating
 *                 rooms in the Faerun.  
 */
public void
create_faerun_room() {}


/*
 * Function name : reset_faerun_room
 * Description   : If you want to reset a room in the Faerun use this function.
 */
void
reset_faerun_room() 
{

    if (sizeof(query_herb_files()))
	this_object()->reset_faerun_herbs();

}

/*
 * Function name : reset_room
 * Description   : Takes care of reseting certain things used in Faerun.
 */
void
reset_room()
{
    reset_faerun_room();
}

/*
 * Function name : query_sunlight
 * Description   : Sets up the Sunlight level of the domain.... used mainly
 *                 as support for the Vampire guild.
 */
nomask public int
query_sunlight()
{
    string time = CLOCK->query_part_of_day();
    int level = 0;

    if (query_prop(ROOM_I_INSIDE))
	return 0;

    switch(time)
    {
    case "night":
	return SUNLIGHT_NIGHT;
    case "evening":
    case "early morning":
	level = SUNLIGHT_DIM;
	break;
    case "afternoon":
    case "morning":
	level = SUNLIGHT_NORMAL;
	break;
    case "noon":
	level = SUNLIGHT_BRIGHT;
	break;
	//  Should never go to default
    default:
	level = 1;
	break;
    }


    //   If a weather master is ever created modify level due to
    //   It being sunny or cloudy out.

    return level;
}

/*
 * This is maskable by areas that may wish to do so.
 * The argument is not currently used.
 */
public int
faerun_time(string str)
{
    string *arr;

	if (this_object()->query_prop(ROOM_I_INSIDE))
	{
		write("It's too difficult to determine the time while indoors.\n");
		return 1;
	}

//    arr = explode(TIME_DESC_LONG, ", ");
//    write(implode(arr[0..1], ", ") + ", " + arr[2] + "\n");

    arr = explode(TIME_DESC_LONG, ", ");
// writes time to user
    write(implode(arr[0..1], ", ")+ ".\n");


    return 1;
}

/* 
 * Function name : init (masked)
 * Description   : sman init for more detals. It's masked here for 
 *                 cmd_parse support.
 */
public void
init()
{
    ::init();

    add_action(faerun_time, "time");
    init_cmdparse();
}

/*
 * Function name : enter_inv 
 * Description   : sman enter_inv for more details.  It's masked here
 *                 for room_tell support.
 */
public void
enter_inv(object ob, object from)
{
    if (sizeof(query_room_tells()))
	start_room_tells();
    ::enter_inv(ob,from);
}


string
season_tell()
{
    int seasons = CLOCK->query_season();
write(seasons);

/*
    switch(seasons)
    {
        case "winter" :
            return "An icy wind blows past you, nipping your face.\n";
        case "spring" :
            return "A cool wind blows by, promising warmer days ahead.\n";
        case "summer" :
            return "A hot, summer breeze blows past you.\n";
        case "fall":
            return "A balmy breeze blows by, promising colder days ahead.\n";
    }
*/
}

public string
long_desc()
{
    string  desc = CAP(query_short()) + ". " + TIME_DESC_ROOM + " ";

    if (strlen(extraline))
        desc += extraline;
    if (functionp(vbfc_extra))
        desc += vbfc_extra();
    return (desc + "\n");

}

/*
 * Function name : create_room
 * Description   : creates the room with all the Standard things we wish to
 *                 have in Faerun. 
 */
public void
create_room()
{
    // These are here for mortals... They usually report wierd long and
    // short desceptions.
    
    setuid(); 
    seteuid(getuid());
    
    extraline = "This is the extra_line description added to personalize the room description.";

    set_short("Faerun outdoor base room file");
//    set_long(short() + ". "  + TIME_DESC_ROOM + " Insert long description here. " + extra_line + "\n");
    set_long(long_desc);
    set_room_tell_time(120 + random(60));
//    set_room_tell_time(5);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Some clouds pass overhead.");
    

    //  The domains sunlight level.
    add_prop("_room_i_sunlight", query_sunlight);
    create_faerun_room();

}
/* Add herbing abilities  */
void 
add_herbs()
{
    int seed;

    seed = file_size(file_name(calling_object()) + ".c");
    add_std_herbs(0, seed);
}

void update_internal(int l, int w, int v)
{
        int lo, ln;

        // old light level
        lo = query_prop(OBJ_I_LIGHT);

        // apply the change
        ::update_internal(l, w, v);

        // light level changed ?
        if (l ==0)
                return;

        ln = query_prop(OBJ_I_LIGHT);
        //tell_room(TO, "-------\nLight level changed from " + lo + " to " + ln + "\n--------\n");

        // light -> dark or dark->light
        // notify players
        if (lo>0 && ln<1) {
                tell_room(TO, "Suddenly darkness engulfs you.\n");
        } else if (lo<1 && ln>0) {
                tell_room(TO, "The darkness withdraws and you can see again.\n");
        }

        // notify all npc's in the room about the new light level
        object *inv, *npcs;
        inv = all_inventory();
        //npcs=FILTER_LIVE(inv) - FILTER_PLAYERS(inv);
        //npcs=inv-filter(inv, living @ query_interactive);

        npcs=filter(all_inventory(), &->query_npc());
        npcs->notify_light_level(ln);
}
