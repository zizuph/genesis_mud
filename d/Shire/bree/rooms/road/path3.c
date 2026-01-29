/*
 * Path behind the AG in Bree.
 * Raymundo, Jan 2020
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit PATH_BASE;



void
create_path_room()
{
    add_bree_desc("You are behind the Adventurer's Guild. The "
        + "grass here is still quite thick and, if anything, "
        + "has seen even less traffic than the rest of the "
        + "path. This is, as they say, the end of the road. "
        + "From here, the path only returns to the north.\n");

    add_AG("east", "There is a door in the back wall, leading "
        + "west, but it looks closed shut. A lattice covered "
        + "in grape vines leads up the side of the building.");
    add_item( ({"vine", "grape vine", "vines", "grape vines"}),
         "The vines grow up the side of the building, toward the "
        + "roof. Unfortunately, you see no ripe grapes on them.\n");
    add_item("lattice", "The lattice is made of surprisingly thick "
        + "boards, fitted together to make square shapes. It leads "
        + "from the ground all the way up to the ceiling and looks "
        + "quite sturdy. There are grape vines growing on it.\n");
    remove_item("wall");
    add_item( ({"wall", "walls"}), "To the west is the rear wall "
        + "of the Adventurer's Guild. It's made of thick heavy "
        + "logs and looks as if it'll last a while. A lattice "
        + "with grape vines on it extends from the ground to "
        + "the roof.\n");
    add_item("roof", "It looks like a pretty standard roof. It extends "
        + "a little ways from the walls, so as to keep the rain from "
        + "running inside.\n");
    add_item("inside", "You're on the outside. If you want to see the "
        + "inside, go back to the main road in Bree and enter the "
        + "Adventurer's Guild.\n");
    add_item( ({"shade", "shadows"}), "Thanks to the roof, you can walk "
        + "here without being baked by the sun.\n");
        
    add_cmd_item("door", "open", "The door is stuck closed!\n");
    add_cmd_item("lattice", "climb", "@@climb_lattice@@");
        
    add_exit(ROAD_DIR + "path2", "north");
    set_no_exit_msg("west", "You try to go through the door, but it is "
        + "shut tight. All you do is hurt your head.\n");

    reset_shire_room();
}



void
reset_shire_room()
{

}

int
climb_lattice()
{
    
    if(TP->query_skill(SS_CLIMB) <= (25+(random(30))))
    {
        write("You try to climb the lattice but cannot get a grip!\n"
            + "OUCH! That hurt!\n");
    //purposely don't call do_die. How do you die falling off a lattice? Lame.
        TP->heal_hp(-100); 
        return 1;
    }
    write("You climb the lattice up to the roof.\n");
    say(QCTNAME(TP) + " climbs the lattice up to the roof.\n");
    tell_room( (ROAD_DIR + "roof1"), QCTNAME(TP) + " arrives "
        + "climbing from below.\n");
    TP->move_living("M", ROAD_DIR + "roof1");
    return 1;
}