/*
 * l2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("Boiling sea of lava");
    set_long("You are standing in the middle of a sea of boiling " +
             "lava. The heat here is really incredible. To the south " +
             "you see a slope which looks like a safe way out of here. " +
             "To your north you see a high stone pillar with some old " +
             "stairs carved in the rock.\n");

    add_exit("e4", "south", "@@block");
    add_exit("s1", "north");
    add_prop(OBJ_I_HAS_FIRE, 1);

}

int
block()
{
    TP->remove_prop(COLDFEET);
    TP->catch_msg("The coldness of your feet disappears.\n");
    return 0;
}
