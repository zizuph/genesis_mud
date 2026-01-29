/*
 * road_1_5.c
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
        "to the immediate east appears to be a shop " +
        "of some sort, while there is a small wooden pier to the west.\n");
 
    add_item("pier",
        "It is a small wooden pier, crudely made of large tree trunks. "+
        "It looks as if it has been weather-beaten and sea-worn for "+
        "many years. You can walk onto it to the west.\n");
 

    add_item(({"building"}),
        "The building to the east looks a bit different " +
        "than the other buildings in the village. It " +
        "is made of the same stones, but the doorway " +
        "has been made wider, and it seems to see a lot " +
        "of traffic.\n");

    add_exit(ROOM + "road_1_4", "north");
    add_exit(ROOM + "shop", "east");
    add_exit(ROOM + "road_1_6", "south");
    add_exit(ROOM + "pier", "west");
    reset_room();
}
