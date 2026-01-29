/*
 * The room base for the village of Que Shu (outside rooms)
 */

#include "/d/Krynn/common/defs.h"
#include CLOCKH
#include "../local.h"
#include <composite.h>
#include <filter_funs.h>

/* Inherit the Krynn room */
inherit OR_FILE

#define CREATE "create_que_shu_room"
#define RESET  "reset_que_shu_room"

/*
 * Here we define some specific things that'll make it easier to
 * write rooms.
 */

int gPlace;
string gShort_desc, gLong_desc;

/*prototypes*/
public void add_tent(string direction);
public void add_tent_exit(string place, string direction);
public void add_arena(string direction);
/*public void add_wall(string direction);
public void add_well(string direction);
public void add_building(string direction);*/


public void
set_place(int i)
{
    gPlace = i;
}

public void
set_short_desc(string str)
{
    gShort_desc = str;
}

public void
set_long_desc(string str)
{
    gLong_desc = str;
}

public void
short_desc()
{
    string str;

    switch (gPlace)
    {
        case MAINPATH:
            gShort_desc = "on the main path in Que Shu";
	    add_arena("south");
	    break;
        case EASTPATH:
	    gShort_desc = "on the east path in Que Shu";
	    add_arena("west");
	    break;
        case WESTPATH:
	    gShort_desc = "on the west path in Que Shu";
	    add_arena("east");
	    break;
	case INTERSECT:
	    gShort_desc = "at the intersection";
	    add_arena("directly next");
	    break;
	case SMALLPATH:
	    gShort_desc = "on a small path";
	    break;
	case NSPATH:
	    gShort_desc = "on a path";
	    break;
	case ARENA:
	    gShort_desc = "at the Que Shu arena";
	    break;
	case WELL:
	    gShort_desc = "at the well of Que Shu";
	    add_arena("northeast");
	    break;
	default:
	    break;
    }
}

public string
long_desc()
{
    string desc;

    desc = "You are " + gShort_desc + ". It is " + GET_TIME_STRING + ". ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
           desc += "The sun becomes visible in they sky, highlighting " +
	           "the tents around you as they prepare " +
		   "for a new day. ";
	   break;
        case TOD_DAY:
	   desc += "The sun is shining down on you. ";
	   break;
        case TOD_TWILIGHT:
	   desc += "The sunlight grows weaker as the day ends. ";
	   break;
        case TOD_NIGHT:
	   desc += "The pale light from the two moons makes the " +
	           "tents cast strange shadows on the ground. ";
	   break;
    }

    desc += check_call(gLong_desc) + " ";

    switch (GET_SEASON)
    {
        case WINTER:
            desc += "The chill of the winter is in the air, and all is pale " +
	            "and frozen. A cold wind sweeps across the plains into the " +
		    "village.";
            break;
	case SPRING:
            desc += "Spring is in the air, awakening the land from the " +
	            "long winter sleep.";
	    break;
        case SUMMER:
            desc += "The land is vibrant with life and color in the warm " +
	            "summer.";
	    break;
	case AUTUMN:
	    desc += "The air grows chill, and though summer is not long " +
	            "gone you know winter will be here soon.";
	    break;
    }

    return desc + "\n";
}

public void
add_tent(string direction)
{
    add_item(({"tent",direction + " tent"}),
	     "There is a tent to your " + direction + ". It is a typical " +
	     "tent of the village, so high you cannot look over it.\n");
}

public void
add_tent_exit(string place, string direction)
{
    add_item(({"tent",direction + " tent"}),
	     "There is a tent to your " + direction + ". It is a typical " +
	     "tent of the village, so high you cannot look over it. There " +
	     "is a flap in the tent.\n");
    add_item("flap",
	     "It is a flap in the tent to enter and leave the tent.\n");
    add_exit(place,direction);
}

public void
add_arena(string direction)
{
    add_item(({"arena","bleachers","spot","round spot"}),
	     "There is a large round spot to the " + direction + ". It appears to " +
	     "be some kind of arena, with bleachers of stone surrounding it. You can " +
	     "get a closer look by going " + direction + ".\n");
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
    call_other(TO, CREATE);

    short_desc();

    set_short(gShort_desc);
    set_long("@@long_desc@@");
    reset();
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

