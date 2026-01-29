// file name:        /d/Avenir/common/holm/jungle/lf1.c
// creator(s):       Lilith, Nov 96
// revisions:
// purpose:
// note:
// bug(s):
// to-do:


/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
#include <ss_types.h>
#include <tasks.h>

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}

int exit_check();
/* Now create the room.  */
void
create_jungle_room()
{
    set_short("Northwest corner of the Holm");
    set_long("The north and west paths come to an end here. Further "+
        "progress to the northwest is blocked by a massive fallen "+
        "tree fern. The air is ripe with the musty smell of decom"+
        "posing wood. Beyond the tree is a narrow promontory of rock "+
        "and a stretch of black-sand beach. You can see the dark "+
        "water of the Sybarus Sea, and hear its constant, gentle "+
        "slapping against the shore. To the southeast is a lowland "+
        "forest, and above it rises a dark spire.\n");

    add_cliff();
    add_item(({"tree", "massive tree", "fallen tree", "moss"}),
        "It is a huge tree-fern draped in moss. It is lodged in "+
        "a break in the wall of stone which parallels the west "+
        "shore of the island.\n");
    add_item(({"wall", "stone", "break"}),
        "There is a break in the wall of stone which runs along "+
        "the western shore of the island. Through it, one can "+
        "reach the promontory and beach at the northwest tip of "+
        "the island. Unfortunately, it is blocked by a decomposing "+
        "tree of massive proportions.\n");
    add_item(({"promontory", "stones"}),
        "The promontory is small, composed of geometric stones "+
        "jutting out of the water. The stones are darker than the "+
        "water, a weathered black colour. It has a beach.\n");
    add_item("beach",
        "The beach is made of black sand. You are unable to deter"+
        "mine its fineness or composition from this distance, but "+
        "it would appear to be made from the endless wearing away "+
        "of the promontory stones by the sea.\n");
    add_item(({"west", "west trail", "west path"}),
        "This path leads west, onto a promontory. Unfortunately, "+
        "it is blocked by a massive tree. The path will likely "+
        "be impassible until the tree has decayed some more."+
        ".\n");  

    add_exit("lf2", "east", 0);
    add_exit("lf6", "south", 0);
    add_exit(SHORE + "sh12", "tree", exit_check);

    reset_domain_room();
}

int
exit_check()
{
    int climb_task;
    climb_task = TP->resolve_task(TASK_ROUTINE, ({ TS_DEX, SS_CLIMB }));

    if (climb_task > 10)
    {
        write("With effort and determination, you work your way "+
            "up the slippery trunk of the fallen treefern, then "+
            "drop down into the sand on the other side of the sea"+
            "wall.\n");
        say("With great effort and determination, "+ QCTNAME(TP) +
            " makes "+ POSSESS(TP) +" way up the slippery trunk "+
            "of the fallen treefern and disappears from your view.\n");
        return 0;
    }
    else
    {
        write("You try to climb your way up the slippery trunk "+
            "of the fallen treefern.\nYou manage to get halfway "+
            "up before you slide back down.\n");
        say(QCTNAME(TP) +" tries to climb up the moss-covered "+
            "trunk of the fallen treefern, but slips half-way "+
            "up and slides back down.\n");
        return 1;
    }    
}