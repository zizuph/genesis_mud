/*
 * q2.c
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
    set_short("on a very, very narrow path");
    set_long("You are on a narrow path leading towards a mountain " +
             "top. It is getting rather steep now, and you feel " +
             "a little tired due to the thin air. Far below you " +
             "is the Kaheda monastery, residing on a small plateau.\n");

    add_exit("q3", "north", -2, 10);
    add_exit("q1", "west", -1, 0);
}
