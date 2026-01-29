/*
 * p.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("Slope on the Carisca volcano");
    set_long("This is a small path leading up to the top of the " +
             "volcano on Carisca island. You see some smoke rising " +
             "from the crater. Looking down you see the east edge " +
             "of the island.\n");

    add_exit("f5", "down");
    add_exit("e3", "up");
}
