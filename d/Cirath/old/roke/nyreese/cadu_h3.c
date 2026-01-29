/*
 * cadu_h3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object tailor;

void
reset_room()
{
    if (tailor)
        return;

    tailor = clone_object(ROKEDIR + "npc/tailor");
    tailor->move_living("X", TO);
}

void
create_room()
{
    set_short("Tailor's shop");

    set_long("This is the shop of Gandril the Tailor. If you bring him " +
             "skins from slain monsters, he can make armours and bags " +
             "from them.\n");

    add_exit("cadu_s3", "south");

    reset_room();
}
