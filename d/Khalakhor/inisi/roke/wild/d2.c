/*
 * d2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("small and narrow path");
    set_long("North of you the path divides into two, but here is is " +
             "almost too narrow to pass, mostly because some loose rocks " +
             "have fallen down from the mountainsides many years ago.\n");

    add_item(({"rock", "rocks"}), "The rocks look very heavy.\n");
    add_exit("d3", "north");
    add_exit("d1", "south");
}
