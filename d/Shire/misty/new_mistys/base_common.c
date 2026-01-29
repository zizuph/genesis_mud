/*
 * File of common routines for all of the Misty Mountains
 */

#include "/d/Shire/sys/defs.h"
#include "defs.h"
inherit AREA_ROOM;
//inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define MIN_STR  100
#define MIN_DEX  100
#define DEF_DIRS ({ "north", "northern", "south", "southern",  \
                    "east", "eastern", "west", "western",  \
		            "northeast", "northeastern", "northwest", "northwestern",  \
                    "southeast", "southeastern", "southwest", "southwestern" })


static string add_sky = "";


string daylight_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "Moonlight";
        case LATE_NIGHT :
            return "Starlight";
        case EARLY_MORNING :
            return "Soft morning light";
        case MORNING:
            return "Gentle sunlight";
        case NOON:
            return "Noon sunlight";
        case AFTERNOON:
            return "Blazing afternoon sunlight";
        case EVENING:
            return "Evening light";
    }
}


string
day_desc()
{
    switch(qhour())
    {
        case EARLY_NIGHT :
            return "early night";
        case LATE_NIGHT :
            return "late night";
        case EARLY_MORNING :
            return "early morning";
        case MORNING:
            return "morning";
        case NOON:
            return "around noon time";
        case AFTERNOON:
            return "afternoon";
        case EVENING:
            return "evening";
    }
}

string
light_type()
{
   switch(qhour())
    {
        case EARLY_NIGHT :
            return "moonlight";
        case LATE_NIGHT :
            return "starlight";
        case EARLY_MORNING :
            return "early morning light";
        case MORNING:
            return "gentle, morning sunlight";
        case NOON:
            return "bright sunlight";
        case AFTERNOON:
            return "blazing sunlight";
        case EVENING:
            return "soft, gentle night light";
    }
}

/*
 * Function name : set_add_sky
 * Description   : adds descr of sky
 */
void set_add_sky()
{
    add_item("sky",
        "It is @@day_desc@@. @@daylight_desc@@ fills the sky.\n");
}

int climb_mt(string str, string next_room, string direction)
{

    if (TP->query_fatigue() < 40)
    {
        write("You are too exhausted to try going up the mountain.\n");
        say(QCTNAME(TP) + " struggles trying to go up the mountain, but " +
            "is utterly exhausted.\n");
        TP->add_fatigue(-10);
        return 1;
    }

    if ( (TP->query_stat(SS_DEX)> MIN_DEX + random(20)) && 
         (TP->query_stat(SS_STR)> MIN_STR + random(20)) )
    {
        write("You struggle through the snow and up the side of the " +
            "mountain.\n");
        TP->add_fatigue(-10);
        return 0;
    }
    
    write("You struggle though the snow drifts but can't move up the " +
        "side of the mountain.\n");
    say(QCNAME(TP) + " struggles through the snow drifts but gives up, " +
        "unable to make it up mountain.\n");
    TP->add_fatigue(-20);
        write("You struggle through the snow and up the side of the " +
            "mountain.\n");
    TP->add_fatigue(-10);
    tell_room(ENV(TP), QCTNAME(TP) + " climbs up a snow drift and disappears.\n",TP);
    TP->move_living("M",PATH_DIR + next_room);
        

    return 1;

}
