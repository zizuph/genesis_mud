/*
 * monk_occtrain1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("training room");
    set_long("This is the largest training room in the monastery. You can see many\n" +
             "priests in training. They look very concentrated. In the far end of the room\n" +
             "you can see the chief-instructor. He is willing to teach you everything he\n" +
             "knows about unarmed combat and other skills.\n" +
             "You can see a big door behind him but you can't see into the next room.\n" +
             "There is a new sign on the wall.\n");
    
    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item(({"instructor", "chief-instructor"}),
             "He looks sturdy and you can see that he knows alot about all " +
             "fighting styles.\n");

    add_item(({"priest", "priests"}),
             "They are training very hard indeed.\n");
    add_item("sign", "You should read it.\n");
    add_cmd_item("sign", "read", "You can now choose " +
                 "between unarmed and armed combat. Simply pray for either: " +
                 "polearm skill or unarmed combat.\n");

    INSIDE;

    add_exit("monk_h2", "west");
    add_exit("monk_occtrain2", "east");
}
