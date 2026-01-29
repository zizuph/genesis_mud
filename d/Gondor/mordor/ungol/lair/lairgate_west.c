/*
 * /d/Gondor/mordor/ungol/lair/lairgate_west.c
 *
 * This 'door' is the gate under Cirith Ungol, connecting the tower with
 * Torch Ungol, Shelobs lair. This side is the door in the tower. You can
 * climb over the door and there is no way to unlock this door from this side.
 */

inherit "/d/Gondor/mordor/ungol/lair/lairgate_base";

#include "/d/Gondor/defs.h"

void create_door()
{
    ::create_door();

    set_lock_desc( "It is on the other side of the gate.\n" );
    set_open_desc( "An open gate, leading east.\n" );
    set_closed_desc( "A closed gate, leading east.\n" );
    set_pass_command( ({ "east", "e" }) );
    set_fail_pass( "As you try to walk east, you bump against the great "+
        "arched gate.\n" );
    set_open_mess( ({
        "opens the strong gate in the east wall.",
        "Suddenly the strong gate in the west wall opens.\n" }) );
    set_fail_open( ({
        "The strong gate in the east wall is already open.\n",
        "The strong gate in the east wall is locked.\n" }) );
    set_close_mess( ({
        "closes the strong gate in the east wall.",
        "Suddenly the strong gate in the west wall closes.\n" }) );
    set_fail_close(    
        "The strong gate in the east wall is already closed.\n" );
    set_other_room( LAIR_DIR + "tunnel11" );
}
