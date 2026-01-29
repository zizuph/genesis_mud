/*
 * Basic room for bin bit quests
 * Finwe, June 2017
 */

#include "../defs.h"

inherit "/std/room";

create_room()
{
    object npc;

    set_short("Fred's room");
    set_long("This is Fred's room..\n");
    add_exit(ROOM_DIR + "home", "back");

    room_add_object(NPC_DIR + "fred");
}
