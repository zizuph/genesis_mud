/*
* o_room_base.c
*
* This is a standard local room base file for out-door rooms.
* You should change all those XXX to something more appropiate.
* If you are doing an area like Pax Tharkas then a proper 
* replacement for XXX would be 'pax'.
*/

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AOR_FILE

#define CREATE "create_seavillage_room"
#define RESET "reset_seavillage_room"

string
climb_cliff()
{
    write("You don't think you have a wish to fall to your death.\n"); 
    say(QCTNAME(TP) + " looks down at the waves crashing "+
      "into the broken rocks far below, and shudders, backing "+
      "away from the edge of the cliff.\n");
    return "";
}

string
tod_descr1()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "It is night time as you travel along this path. ";
	break;
    case TOD_DAWN:
	str = "It is dawn as you travel along this path. ";
	break;
    case TOD_DAY:
	str = "It is day time as you travel along this path. ";
	break;
    case TOD_TWILIGHT:
	str = "It is evening as you travel along the path. ";
	break;
    }
    return str;
}

string
tod_descr2()
{
    string str;
    switch (GET_TIME_STRING)
    {
    case MIDNIGHT:
    case NIGHT:
	str = "Far above you, birds wheel in the night sky. ";
	break;
    case EARLY_MORNING:
    case MORNING:
	str = "The sun is climbing higher into the sky, "+
	"casting its light far and wide. ";
	break;
    case EVENING:
	str = "The setting sun throws off brilliant colours of orange and " +
	"red, as it sinks below the clouds to the south. ";
	break;
    case NOON:
    case AFTERNOON:
	str = "The sun has reached its zenith, and is now "+
	"tracing a lazy path downwards in the sky. ";
	break;

    }
    return str;
}


string
season_descr()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	str = "The feel and smell of spring is in "+
	"the air all around you. ";
	break;
    case SUMMER:
	str = "The stinking heat of summer covers the land "+
	"in a miasma of oppressive humidity. ";
	break;
    case AUTUMN:
	str = "From the cool wind blowing over you, "+
	"it seems like the cold of winter is not far "+
	"from this land. ";
	break;
    case WINTER:
	str = "The icy winds roaring across the land "+
	"rapidly steal any warmth from you. "+
	"Winter is upon you with a vengeance. ";
	break;
    }
    return str;
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

    add_item(({"ocean","sea"}),"The ocean, far beneath you, "+
      "looks rough and cold, with the wind whipping the "+
      "waves viciously.\n");

    add_item(({"kalaman","city","Kalaman"}),"The mighty city of "+
      "Kalaman lies far away to the southwest of you, tucked "+
      "away in a bay at the mouth of the Vingaard river.\n");

    add_item("path","The path that you are travelling along "+
      "is desolate and windswept, and looks like it sees little "+
      "traffic these days.\n");

    add_item("bay","Far below, at the bottom of the cliffs lies "+
      "the bay that ships use to reach Kalaman by sea.\n");

    add_item(({"ship","ships"}),"There are no ships at sea at "+
      "the moment.  Perhaps the war keeps them away.\n");

    add_item(({"cliff","cliffs","high cliff","high cliffs"}),
      "These high cliffs are made of crumbling sandstone, and "+
      "look far too dangerous to consider climbing.\n");

    add_cmd_item(({"down cliff","cliff","cliffs","down","down cliffs"}),
      "climb","@@climb_cliff");
}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}


