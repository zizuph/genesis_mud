/*
 * pig_tmp_room.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*
 *   A temporary room for the mail pigeons. Nobody is supposed to come here.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

void
create_room()
{
    set_short("Waiting room");
    set_long("You are in the very room where the carrier pidgeons take a " +
             "rest after a long journey. Please leave them alone.\n");
}
