/*
 * road_1_8.c
 *
 * This is part of a road in Tabor Sogh.
 *
 * Khail - Jan 3/98
 */
#pragma strict_types

#include "room.h"

inherit ROADBASE;
object npc;
 
public void
check_npc()
{
   if (objectp(npc)) return;
   npc=clone_object(VILLAGER);
   npc->arm_me();
   npc->move(this_object());
}
 
public void
reset_room()
{
   check_npc();
}
 

public void
create_road()
{
    set_short("narrow dirt road");
    set_long("   You are on a narrow dirt road leading " +
        "north and south through a sleepy little " +
        "fishing village called Tabor Sogh. It appears " +
        "this is the only road in the village, with " +
        "low stone buildings standing on the east " +
        "side, and the rocky shoreline of the Lear " +
        "Min following it to the west. The building " +
        "to the immediate east appears to be a " +
        "gathering place of some sort.\n");

    add_item(({"building"}),
        "The building to the east of here could " +
        "be someone's home, though it appears to " +
        "see a bit more traffic. Perhaps a pub " +
        "or tavern of some sort.\n");

    add_exit(ROOM + "road_1_7", "north");
    add_exit(ROOM + "pub", "east");
    add_exit(ROOM + "road_1_9", "south");
    reset_room();
}
