/*
 * Trail in the Grasslands near the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

#define MIN_TRACKING    30 
#define MIN_AWARENESS   30
#define BUSH_PROP "_found_bandit_path"

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("an old stone road");
    set_extraline("Tall hills obscure your view of the road. They line " +
        "the western side of the mountains. The road does runs roughly north " +
        "and south and looks well travelled.");

    reset_faerun_room();

    add_grasslands();
    add_highroad();
    add_hills();
    add_sword_mts();
    add_std_herbs("hills");

    remove_item("bushes");
    add_item(({"bushes"}),
        "They are all sizes and shapes, and grow scattered everywhere. " +
        "They are low plants with many branches that spread outward. Some " +
        "appear thicker than others.\n");
    add_item("thick bushes",
        "They are taller than others around here. They are taller, too, and almost resemble low trees.\n");
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_exit(HR_DIR + "srd12", "northwest");
    add_exit(HR_DIR + "srd14", "east");

}

public void
init()
{
    ::init();
    add_action("enter_bushes", "enter");
}

void
reset_faerun_room()
{
    set_searched(0);
}


/*
 * search routine to find entrance in bushes
 */
mixed do_search(object searcher, string str)
{
    int awareness, tracking;

//    setuid(); 
//    seteuid(getuid());

    if (!parse_command(str, ({}),
       "'bushes' [the] [thick]"))

        return 0;

    awareness = searcher->query_skill(SS_AWARENESS);
    tracking  = searcher->query_skill(SS_TRACKING);
    if (awareness >= MIN_AWARENESS && tracking >= MIN_TRACKING)
    {
        TP->add_prop(BUSH_PROP,1);
        return "You find a hidden opening in the thick bushes.\n";
    }

    return 0;
}


int
enter_bushes(string str)
{
    if( str=="bushes" ||
        str=="thick bushes" || 
        str=="hidden opening" || 
        str=="opening")
    {
        if(TP->query_prop(BUSH_PROP))
        {    
            //Kehr - fixed double "the": write("You enter the the thick bushes.\n");
            write("You enter the thick bushes.\n");
            say(QCTNAME(TP)+" disappears into the bushes.\n");
            tell_room(HR_DIR + "btr01",QCTNAME(TP) + " arrives.\n");
	        TP->move_living("M", HR_DIR + "btr01",1);
	   
            return 1;
        }
        else
        write("You do not see any "+str+" to enter here.\n");
        return 1;
    }
    notify_fail("Enter what?\n");
    return 0;
}
