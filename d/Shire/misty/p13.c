/* highpass */

#include "local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit SHIRE_ROOM;

#define BUSH_PROP "_i_found_the_cave_"
#define MIN_STATS 20
#define MIN_STR 75
#define ORC_ENTRANCE     "/d/Shire/log/orc_entrance"
#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))


// string bush_check();

void
create_shire_room()
{
    set_short("at foot of mountains");
    set_long("You are at the foot of Misty Mountains. To the west you " + 
      "can see only huge peaks. The path goes through the saddle " +
      "high up. To the east there is a straight path towards dark " +
      "Mirkwood. Scraggly bushes grow alongside the path.\n");

    add_item("peak", "The peaks are high and dark.\n");
    add_item("peaks", "The peaks are high and dark.\n");
    add_item("saddle", "It is a natural saddle between two high peaks.\n");

    add_item(({"bushes", "scraggy bushes"}),
        "They are windswept and unusually scraggly. They are tall and thick, " +
        "growing alongside the path. @@exa_bush@@\n");
//    add_prop("_obj_s_search_fun","do_search");

    set_room_tell_time(45+random(15));
	add_room_tell("A scuffling sound comes from the bushes nearby.");
	add_room_tell("Something nearby grunts briefly.");
    
    /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"p12", "southwest",    0,    8);
    add_exit("/d/Shire/anduin/west/rd06", "east", 0, 6);
    //add_exit("/d/Shire/misty/orc_area/oa1", "north", 0, 5);	

}
/*
string
do_search(object searcher, string str)
{
    int awareness;
    int tracking;
    int hunting;
    int strength;

    awareness = searcher->query_skill(SS_AWARENESS);
	tracking = searcher->query_skill(SS_TRACKING);
	hunting = searcher->query_skill(SS_HUNTING);
    str = searcher->query_stat(SS_STR);

    if (awareness < MIN_STATS + random(4) &&
        tracking < MIN_STATS + random(4)  && 
        hunting < MIN_STATS + random(4)   &&
        strength < MIN_STR)) return 0;

    if(str == "bushes" || str == "scraggly bushes")
    {
        searcher->add_prop(BUSH_PROP, 1);    
        return "You find an opening in the bushes.\n";
    }
    return "";
}
*/
void
init()
{   
    ::init();
 
    add_action("enter_bushes", "enter");
}

mixed
enter_bushes(string str)
{

    if(str=="opening" || 
       str=="bushes")
    {
        if(TP->query_prop(BUSH_PROP))
        {    
            write("You enter the bushes.\n");
            say(QCTNAME(TP)+" disappears into the bushes.\n");
            tell_room(MISTY_DIR +"/orc_area/oa1",QCTNAME(TP) + " arrives.\n");
	        TP->move_living("M", MISTY_DIR +"orc_area/oa1",1);
// log who enters the bushes

    if (file_size(ORC_ENTRANCE) > 50000)
    {
	    rename(ORC_ENTRANCE, (ORC_ENTRANCE + ".old"));
    }

        write_file(ORC_ENTRANCE, (ctime(time()) + " "+  WRITE_NAME(TP) + " " + "(" +TP->query_average_stat() + ") entered the bushes to Orc Guild.\n"));
            return 1;
        }
        else
            write("You can't seem to do that.\n");
        return 1;
    }
    notify_fail("Enter what?\n");
    return 0;
}

string
exa_bush()
{
    int awareness;
    int tracking;
    int hunting;
    int strength;

    awareness = TP->query_skill(SS_AWARENESS);
	tracking = TP->query_skill(SS_TRACKING);
	hunting = TP->query_skill(SS_HUNTING);
    strength = TP->query_stat(SS_STR);
 
    if (awareness < MIN_STATS + random(4) &&
        tracking < MIN_STATS + random(4)  && 
        hunting < MIN_STATS + random(4)   &&
        strength < MIN_STR) 
        return "";
    else

    {
        TP->add_prop(BUSH_PROP, 1);    
        return "You find an opening in the bushes.";
//        return "";
    }
}


bush_check()
{
    if(TP->query_prop(BUSH_PROP))
    {
        return ("There is an opening in the bushes.");
    }
    return "";

}