/*
   Wayreth. Stairwell in tower.

   stairwell11.c
   -------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 95/06/14
   By ...........: Jeremiah

*/

#include "../guild.h"
inherit TOWERROOM;

object    dranin;


void
reset_tower_room()
{
    
    if (dranin)
        return;
    
    dranin = clone_object(NPC + "walk_red");
    dranin->move_living("xx", this_object());
    dranin->seq_new("do_thing");
    dranin->seq_addfirst("do_thing","@@start_patrol");
    
}

void
create_tower_room()
{
    setuid();
    seteuid(getuid());

    set_short("Stairwell on the eleventh level in the tower");
    set_long("You are standing at the top of a spiral stair in a small " +
        "circular stairwell. The spiral stair spins downwards " +
        "around the center of the stairwell, thus each step reaches " +
        "from the wall and to the center of the room. A large " +
        "doorway leads west. The stair leads down towards the " +
        "lower levels of the tower.\n");
    
    set_wall_type(3);
    
    add_item(({"stair", "stairs"}), "The stairs are carved from the same " +
        "dark obsidian as the tower itself. Each step reaches from " +
        "the wall and to the center of the stairwell, around which " +
        "the spiral stair rotates.\n");
    
    add_item(({"step", "steps"}), "Steps carved of dark obsidian. The " +
        "steps are very wide at the wall and narrows towards the " +
        "center of the room.\n");
    
    add_item(({"doorway", "large doorway"}), "A doorway leading west, " +
        "giving access to whatever lies on this level of the tower. " +
        "There is a very vague shimmering in the air, screening the " +
        "doorway.\n");
    
    add_exit("laboratory", "west", "@@pass_check");
    add_exit("stairwell10", "down", 0);

    reset_tower_room();
}
