// file name:        /d/Avenir/common/holm/shore/sh12.c
// creator(s):       Lilith, April 97
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/shore/shore_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}


#include <ss_types.h>
#include <tasks.h>

int check();

/* Now create the room.  */
void
create_shore_room()
{
    set_short("Narrow stretch of black sand leading to a promontory");
    set_long("There is a narrow break in the obsidian seawall, "+
        "blocked by a fallen treefern. The promontory looms "+
        "in the northwest, a lumbering leviathan slowly "+
        "emerging from the dark and secretive waters of the "+
        "Sea of Sybarus.\n");
    add_item(({"tree", "treefern", "fallen tree"}),
        "It is a huge tree-fern draped in moss. It is lodged "+
        "in a break in the obsidian seawall that allows passage "+
        "to and from the jungle.\n");
    add_beachs();
    add_exit(JUNG +"lf1", "tree", "@@check", 5);
    add_exit("sh11", "west", 0, 5);
    add_exit("sh2", "northwest", 0, 5);

    reset_domain_room();
}

int
check()
{
    int climb_task;
    climb_task = TP->resolve_task(TASK_ROUTINE, ({ TS_DEX, SS_CLIMB }));

    if (climb_task > 0)
    {
        write("With the ease of an acrobat, you swing yourself "+
            "up onto the fallen treefern, then slide down its "+
            "trunk.\n");
        say("With the agility and ease of an acrobat, "+ 
            QCTNAME(TP) +" swings "+ OBJECTIVE(TP) +"self "+
            "up onto the trunk of the fallen treefern and "+
            "disappears from your view.\n");
        return 0;
    }
    else
    {
        write("You jump up and grasp a branch projecting "+
            "from the fallen treefern.\nYou try to swing "+
            "yourself up onto it, but fail.\n");
        say(QCTNAME(TP) +" tries to swing "+ OBJECTIVE(TP) +
            "self up onto the fallen treefern, but fails.\n");
        return 1;
    }    
}
