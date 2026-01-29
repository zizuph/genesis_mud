/*
 * boat.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

/* A temporary room to store players while shipping them from the island. */
void
create_room()
{
    set_short("");
    
    set_long("\n");
}
