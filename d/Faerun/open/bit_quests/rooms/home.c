/*
 * Basic room for bin bit quests
 * Finwe, June 2017
 */

#include "../defs.h"

inherit "/std/room";

create_room()
{
    object npc;

    set_short("Georgette's room");
    set_long("This is Georgette's room. She thinks she's all that, and " +
        "a bag of chips. If you ask her for a task, she will give you one.\n");
    add_exit(ROOM_DIR + "fred_room", "fred");
    add_exit(ROOM_DIR + "larry_room", "larry");
    add_exit(ROOM_DIR + "thomas_room", "thomas");
    add_exit(ROOM_DIR + "curly_room", "curly");

    room_add_object(NPC_DIR + "qm");
}
