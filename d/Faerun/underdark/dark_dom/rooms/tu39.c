/*
 * Tunnel room in Underdark
 * Entrance to the Drow.
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

#define MIN_TRACKING    30 
#define MIN_AWARENESS   30
#define CRACK_PROP "_found_drow_crack"

string extraline = "The walls are irregular and cracked. They are cold and black, running through the mountain.";

void
create_tunnel()
{
    add_std_herbs("underdark");

    set_short("A dark tunnel");
    set_extraline(tun_desc1(extraline));

    add_item(({"cracks", "crack"}),
        "They are narrow, vertical breaks in the rock and walls. They were created eons ago as the rock has shifted.\n");
    add_item(({"wall", "walls"}),
        "The walls are naturally carved from the rock. They are irregularly shaped and rough looking, arching overhead to form a rough ceiling above you. There are cracks in them.\n");
    
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();

    add_exit(TUN_DIR + "tu32", "northwest");
    add_exit(TUN_DIR + "tu43", "south");
}

public void
init()
{
    ::init();
    add_action("enter_crack", "enter");

}
void
reset_room()
{
    make_goblins();
    set_searched(0);
}

/*
 * search routine to find entrance in wall
 */
mixed do_search(object searcher, string str)
{
    int awareness, tracking;

    if (!parse_command(str, ({}),
       "'cracks' / 'crack' / 'wall' [the] [large] "))

        return 0;

    awareness = searcher->query_skill(SS_AWARENESS);
    tracking  = searcher->query_skill(SS_TRACKING);
    if (awareness >= MIN_AWARENESS && tracking >= MIN_TRACKING)
    {
        TP->add_prop(CRACK_PROP,1);
        return "You find a hidden opening in the wall.\n";
    }

    return 0;
}


int
enter_crack(string str)
{
    if( str=="cracks" ||
        str=="crack" || 
        str=="fissure" || 
        str=="wall" ||
        str=="opening")
    {
        if(TP->query_prop(CRACK_PROP))
        {    
            write("You enter a crack in the wall.\n");
            say(QCTNAME(TP)+" disappears into a crack in the wall.\n");
            tell_room("/d/Faerun/guilds/drow/rooms/join",QCTNAME(TP) + " arrives.\n");
	        TP->move_living("M", "/d/Faerun/guilds/drow/rooms/join",1);
	   
            return 1;
        }
        else
        write("You do not see any "+str+" to enter here.\n");
        return 1;
    }
    notify_fail("Enter what?\n");
    return 0;
}

