/*
 * Tunnel room in Underdark
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_TUNNEL;

//string extraline = "The tunnel ends, but climbs up and around a giant stalagmite hanging down from the ceiling.";
string extraline = "The tunnel ends, but climbs up and around a giant stalactite hanging down from the ceiling.";

string up_room = TUN_DIR + "cv06";
void up_column();

void
create_tunnel()
{
    add_std_herbs("underdark");

    set_short("A dark tunnel");
    set_extraline(tun_desc5(extraline));

//    add_item(({"stalagmite", "giant stalagmite", "stalacmite", "giant stalacmite", "column", "giant white column", "white column"}),
    add_item(({"stalactite", "giant stalactite", "stalagtite", "giant stalagtite", "column", "giant white column", "white column"}),
        "It is white colored and of immense size. The column stretches " +
        "from the ground up into the depths of the ceiling. It is so " +
        "big it is impossible to tell what it is. Nonetheless, there " +
        "is a path that climbs up and around it.\n");
    reset_room();

    add_exit(TUN_DIR + "tu23", "southeast");
    add_exit(TUN_DIR + "cv06", "up");

}

public void
init()
{
    ::init();
//    add_action("do_climb", "climb");
//    if (interactive(this_player()))
//        catch(call_other("/d/Faerun/underdark/dark_dom/npc/clone_handler.c", "??"));


}
void
reset_room()
{
    set_searched(0);
} 

int do_climb(string str)
{

/*    if(str =="tree" || str == "branch")
    {
        write("Do you want to climb up or down?\n");
        return 1;
    }*/

    if(str=="up")
    {
        up_column();
        return 1;
    }
       
//    write("Climb up or down?\n");
    write("Climb up?\n");
    return 1;
}


void up_column()
{
    write("You follow a path up, around, and behind the column.\n\n");
    say(QCTNAME(TP) + " disappears behind the column.\n");
    TP->move_living("M",up_room);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from below.\n",TP);
}
