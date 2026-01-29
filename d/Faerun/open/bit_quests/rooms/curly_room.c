/*
 * Basic room for bin bit quests
 * Finwe, June 2017
 */

#include "../defs.h"

inherit "/std/room";

create_room()
{
    object npc;

    set_short("Curly's room");
    set_long("This is Curly's room. He can be a whack-a-doodle sometimes.\n");
    add_exit(ROOM_DIR + "home", "back");

    room_add_object(NPC_DIR + "curly");
}
