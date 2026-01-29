#include "plains.h"

inherit PLAINBASE;

public void
reset_room()
{
   set_searched(0);
}


public void
create_khalakhor_room()
{
    create_plain();
    set_short("In a pasture on a grassy plain");
    set_long("   You are at the entrance of a pasture situated on the "+
             "grassy rolling hills of the plain. The smell of "+
             "livestock is strong here, the scent mixing with that of "+
             "the salt air brought in by a cool breeze. There is an "+
             "entrance to the pasture through the fence which encloses "+
             "the pasture to the west.\n");

    add_item(({"area","fenced-in area","pasture"}),
       "The pasture is situated on the grassy hills of the plain, "+
       "obviously made to enclose livestock. A crude wooden fence "+
       "surrounds the pasture on all sides.\n");
    add_item("fence",
       "The fence is crudely made of twisted, sun and rain warped "+
       "wooden beams, posts set fairly evenly around the pasture, "+
       "with two rails strapped horizontally between each. There "+
       "is a small entrance in the fence to the west.\n");

    add_exit(PLAINS + "plains_28_7", "north");
    add_exit(PLAINS + "plains_29_7", "northeast");
    add_exit(PLAINS + "plains_29_8", "east");
    add_exit(PLAINS + "plains_29_9", "southeast");
    add_exit(PLAINS + "plains_28_9", "south");
    add_exit(PLAINS + "plains_27_8", "west", "@@check_npc");
}

public int check_npc()
{
   if ((this_player())->query_npc()) return 1;
   return 0;
}

public int *
query_global_coords()
{
    return ({3, 0});
}
