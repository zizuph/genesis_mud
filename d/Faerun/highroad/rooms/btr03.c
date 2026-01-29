/*
 * Trail to the bandit hideout near the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;

#define MIN_TRACKING    30 
#define MIN_AWARENESS   30
#define BUSH_PROP "_found_bandit_cave"

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("a hidden trail in the hills");
    set_extraline("Trees and bushes grow in clumps on the hill. Bunches of grass grow scattered here.");

    reset_faerun_room();
    add_bandit_path("ends here.");
    add_sword_mts();

    remove_item("bushes");
    add_item(({"bushes"}),
        "They are all sizes and shapes, and grow scattered everywhere. " +
        "They are low plants with many branches that spread outward. Some " +
        "appear thicker than others. @@check_bushes@@\n");
    add_item("thick bushes",
        "They are taller than others around here, and almost resemble low trees. @@check_bushes@@\n");
    add_bandit_path("runs north.");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_exit(HR_DIR + "btr02", "north");

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
}

/*
 * search routine to find entrance in bushes
 */
mixed do_search(object searcher, string str)
{
    int awareness, tracking;

    if (!parse_command(str, ({}),
       "'bushes' [the] [large] [maple]"))

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
            write("You enter the the thick bushes.\n");
            say(QCTNAME(TP)+" disappears into the bushes.\n");
//            tell_room(BANDIT_DIR + "entr",QCTNAME(TP) + " arrives.\n");
//            TP->move_living("M", BANDIT_DIR + "entr",1);
            tell_room("/d/Faerun/highroad/rooms/bandits/entr",QCTNAME(TP) + " arrives.\n");
            TP->move_living("M", "/d/Faerun/highroad/bandits/rooms/entr",1);

       
            return 1;
        }
        else
        write("You do not see any "+str+" to enter here.\n");
        return 1;
    }
    notify_fail("Enter what?\n");
    return 0;
}

string check_bushes()
{
    if(TP->query_prop(BUSH_PROP))
    {    
        return "A large opening is visible in the bushes.";
    }
    return "";
    
}
