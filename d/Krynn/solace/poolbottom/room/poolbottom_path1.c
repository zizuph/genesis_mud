#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit POOLBOTTOM_OUT;

void
reset_poolbottom_room()
{
	return;
}

create_poolbottom_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"large stone building","stone building","building","wing",
         "wings","structure","main structure","large building","outline",
         "two storey stone building","second storey","east wing", "west wing"}),
       "@@far_building");

    add_item(({"windows","window","lights"}),
       "@@windows");

    add_exit(ROOM + "poolbottom_path2","northeast",0);
    add_exit("/d/Krynn/solace/lake/room/lake3","southwest",0);

    reset_poolbottom_room();
}

string
short_descr()
{
    return far_school_desc();
}

string
long_descr()
{
    return long_far_desc()+"\n";
}

string
far_building()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "In the distance, outlined against the darkness of night, you can make out a large stone building, " +
              "dimly illuminated by lights high up in a number of second storey windows.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "In the distance you can make out a large two storey stone building, with " +
                  "two wings extending to the east and west of the main structure.\n";
	    break;
    }
    return str;
}

string
windows()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "In the distance a number of windows twinkle like beacons in the night " +
               "from the dim outline of a large building.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "A number of windows can be made out high up on the second storey of the " +
               "large building.\n";
	    break;
    }
    return str;
}
