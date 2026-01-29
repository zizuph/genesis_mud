/* File: sky */
/* sky above the volcano in the land of the dinosaurs */
/* This room is used for the pteranodon to fly in */

inherit "/std/room";

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void create_room()
{
    set_short("Sky above the volcano");
    set_long(break_string("This is the sky above the volcano. It's a "
        + "place where pteranodons like to fly around.\n",70));
}
