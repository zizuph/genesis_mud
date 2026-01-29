/*
 * road_1_3.c
 *
 * This is part of a road in Tabor Sogh, outside villag kirk
 *
 * Khail, Zima - Jan 3/98
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
        "to the immediate east appears to be a small kirk.\n");
 
    add_item(({"building","kirk"}),
        "The building to the immediate east is identical " +
        "to almost all of the buildings in the village, " +
        "low stone walls with a thatched roof. However " +
        "it seems a little larger than most and has a sacred "+
        "look to it.\n");
 
    add_exit(ROOM + "road_1_2", "north");
    add_exit(ROOM + "kirk1",    "east");
    add_exit(ROOM + "road_1_4", "south");
    reset_room();
}
