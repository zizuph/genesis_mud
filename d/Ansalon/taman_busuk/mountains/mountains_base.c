/*
 *    The base file for Taman Busuk 
 *
 *    mountains_base.c
 *    ----------------
 *
 *    Coded .........: 98/07/23
 *    By ............: Ashlar
 *
 *    Latest update .: 98/07/23
 *    By ............: Ashlar
 *
 *
 *    Notes ..:
 *
 *    Changes :
 *       Stralle 040328 - made herbdistribution more static from room to room
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include <math.h>
#include DL_CLOCK
#include "describe.h"

/* Inherit the Ansalon room */
inherit AOR_FILE
inherit HERBSEARCHNEW;

#define CREATE "create_mountains_room"
#define RESET "reset_mountains_room"

#define TB_MOUNTAIN 0
#define TB_VALLEY   1

static int terrain;
string extra_long_descr = "";
static string *herbs = ({ });
static string *herb_places = ({ });

#ifndef ONE_OF
#define ONE_OF(x)   ((x)[random(sizeof(x))])
#endif  ONE_OF

void set_mountain()
{
    string *arr = explode(file_name(this_object()), "/");
    
    terrain = TB_MOUNTAIN;
    herbs = HERB_MASTER->query_herbs( ({ "mountains", }) );

    herb_places = ({ "ground", "rocks", "growth" });

    find_player("stralle")->catch_tell("DEBUG: " + arr[sizeof(arr) - 1] + "\n");

    herbs = ({ herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477830, sizeof(herbs))],
        herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477831, sizeof(herbs))],
        herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477832, sizeof(herbs))],
        herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477833, sizeof(herbs))],
        herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477834, sizeof(herbs))] });
}
void set_mountain_road()
{
    terrain = TB_MOUNTAIN;
}
void set_valley()
{
    string *arr = explode(file_name(this_object()), "/");

    terrain = TB_VALLEY;
    herbs = HERB_MASTER->query_herbs( ({ "conifforest", }) );
    herb_places = ({ "ground", "undergrowth", "bushes" });

    find_player("stralle")->catch_tell("DEBUG: " + arr[sizeof(arr) - 1] + "\n");
    herbs = ({ herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477830, sizeof(herbs))],
        herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477831, sizeof(herbs))],
        herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477832, sizeof(herbs))],
        herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477833, sizeof(herbs))],
        herbs[NAME_TO_RANDOM(arr[sizeof(arr) - 1], 76477834, sizeof(herbs))] });
}
void set_valley_road()
{
    terrain = TB_VALLEY;
}

string
mountain_season_desc()
{
    string str;
    switch(GET_SEASON)
    {
    	case SPRING:
	        str = "The spring air is crisp up here in " +
        	"the mountains. ";
        	break;
    	case SUMMER:
	        str = "Summer has dispelled the last vestiges of " +
	        "snow among the mountains. ";
        	break;
    	case AUTUMN:
	        str = "Autumn chill is in the air, and snow " +
        	"is creeping down from the highest peaks. ";
        	break;
    	case WINTER:
	        str = "The winter cold is intense up here in " +
        	"the mountains, and snow covers everything. ";
        	break;
    }
    return str;
}

string
mountain_tod_desc()
{
    string str;

    switch(GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            str = "It is night in the Taman Busuk mountain range. ";
        break;
        case TOD_DAWN:
            str = "It is morning in the Taman Busuk mountain range. ";
        break;
        case TOD_DAY:
            str = "It is day in the Taman Busuk mountain range. ";
        break;
        case TOD_TWILIGHT:
            str = "It is evening in the Taman Busuk mountain range. ";
        break;
    }

    switch(GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str += "The landscape looks stark and barren illuminated " +
            "by the light of the stars. ";
        break;
        case EARLY_MORNING:
            str += "The eastern horizon is ablaze in an amazing " +
            "hue of orange, as the early morning sun rises. ";
        break;
        case MORNING:
        case AFTERNOON:
            str += "The sun casts long shadows among the mountain " +
            "peaks. ";
            break;
        case NOON:
            str += "The noon sunlight feels very strong at this " +
            "altitude. ";
            break;
        case EVENING:
            str += "The sun is sinking below the west horizon, " +
            "shrouding the landscape in shadow. ";
        break;
    }

    return str;
}

string
valley_season_desc()
{
    string str;
    switch(GET_SEASON)
    {
    	case SPRING:
	        str = "Spring brings new life to this " +
        	"mountain valley. ";
        	break;
    	case SUMMER:
        	str = "Summer has brought verdant green " +
        	"growth to the mountain valley. ";
        	break;
    	case AUTUMN:
        	str = "Autumn brings cool winds to this mountain " +
        	"valley. ";
        	break;
	    case WINTER:
        	str = "A blanket of snow covers the mountain valley. ";
        	break;
    }
    return str;
}

string
valley_tod_desc()
{
    string str;

    switch(GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            str = "It is night in the Taman Busuk mountain range. ";
        break;
        case TOD_DAWN:
            str = "It is morning in the Taman Busuk mountain range. ";
        break;
        case TOD_DAY:
            str = "It is day in the Taman Busuk mountain range. ";
        break;
        case TOD_TWILIGHT:
            str = "It is evening in the Taman Busuk mountain range. ";
        break;
    }

    switch(GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str += "The landscape looks stark and barren illuminated " +
            "by the light of the stars. ";
        break;
        case EARLY_MORNING:
            str += "A soft glow of orange can barely be sensed over " +
            "the eastern edge of the valley. ";
        break;
        case MORNING:
        case AFTERNOON:
            str += "The sun casts long shadows on the valley floor. ";
            break;
        case NOON:
            str += "The noon sunlight feels very strong at this " +
            "altitude. ";
            break;
        case EVENING:
            str += "The sun is sinking below the west horizon, " +
            "shrouding the valley in shadow. ";
        break;
    }

    return str;
}

string
season_desc()
{
    string str;

    switch(terrain)
    {
    	case TB_MOUNTAIN:
	        str = mountain_season_desc();
        	break;
    	case TB_VALLEY:
	        str = valley_season_desc();
        	break;
    }

    return str;
}


string
tod_desc()
{
    string str;

    switch(terrain)
    {
        case TB_MOUNTAIN:
            str = mountain_tod_desc();
            break;
        case TB_VALLEY:
            str = valley_tod_desc();
            break;
    }

    return str;
}

void
set_extra_long(string str)
{
    extra_long_descr = str;
}

string
long_descr()
{
    string str;

    str = tod_desc() + extra_long_descr + " " + season_desc() + "\n";

    return str;
}

string
ground_desc()
{
    string str;

    if (query_short() == V1_S)
    {
        switch(GET_SEASON)
        {
            case WINTER:
                str = "The ground is covered with a thick layer of " +
                "snow, making travel difficult.";
                break;
            default:
                str = "The ground here in the valley is soil and mixed " +
                "rocks, covered with small bushes and undergrowth.";
        }
    }
    else
    {
        switch(GET_SEASON)
        {
            case WINTER:
                str = "The ground is covered with a thick layer of " +
                "snow, making travel difficult.";
                break;
            default:
                str = "The ground up here in the mountains is mostly " +
                "rock.";
        }
    }

    return str;
}

string
snow_desc()
{
    string str;
    switch(GET_SEASON)
    {
        case WINTER:
            str = "Everything here is covered with a thick layer of " +
            "cold snow.";
            break;
        default:
            str = "The snow on the mountain peaks is too far away " +
            "examine closely.";
    }
    return str;
}

/*
 * Utility functions
 */

int
mountain_tired()
{
    switch(GET_SEASON)
    {
        case WINTER:
            return 60;
        default:
            return 4;
    }
}

int
road_tired()
{
    switch(GET_SEASON)
    {
        case WINTER:
            return 15;
        default:
            return 1;
    }
}

int
valley_tired()
{
    switch(GET_SEASON)
    {
        case WINTER:
            return 15;
        default:
            return 3;
    }
}

varargs object
clone_npc(string file, int do_not_arm)
{
    object ob;

    if (!stringp(file) || (file == ""))
        return 0;

    ob = clone_object(file);
    if (!objectp(ob))
        return 0;

    if (!do_not_arm && function_exists("arm_me",ob))
        ob->arm_me();

    ob->move_living("xxx",this_object());

    return ob;
}

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}


/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    set_long("@@long_descr");
    setuid();
    seteuid(getuid());

    call_other(TO, CREATE);

    switch(query_short())
    {
        case R1_S:
            set_mountain_road();
            break;
        case R2_S:
            set_valley_road();
            break;
        case V1_S:
            set_valley();
            break;
    }

    if (sizeof(herbs))
    {
        set_up_herbs(herbs, ({ "roadside", "ground", "growth",
            "herb growth" }), 3);
#ifdef 0
        set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
            ONE_OF(herbs), ONE_OF(herbs) }), ({ "roadside", "ground",
            "growth", "herb growth" }), 3 );
#endif
    }

    reset_room();
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    this_object()->set_searched(random(6));
    call_other(TO, RESET);
}
