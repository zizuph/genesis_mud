/*
 * common.c
 *
 * Creator: Shadowlynx
 * Date: June/97
 *
 * a common room, common bulletin board present
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"

void load_board();

void
create_room()
{
    set_short("The common board");
    set_long("You are standing in a strange looking room. You" +
      " gasp in amazement at the cleanliness of the place. The" +
      " usual clutter of papers, bells and whistles are not in" +
      " evidence here. The room is entirely bare except for a" +
      " common board which you know to be common to all in the" +
      " realms.\n");

    add_prop(ROOM_I_NO_ATTACK,1);

    add_exit(ROOMS + "joinroom", "down", 0);

    load_board();
}

void
load_board()
{
    object bb;

    seteuid(getuid(TO));
    bb = clone_object("/d/Genesis/obj/board");
    bb->move(this_object());
}
