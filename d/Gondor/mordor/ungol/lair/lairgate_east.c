/*
 * /d/Gondor/mordor/ungol/lair/lairgate_east.c
 *
 * This 'door' is the gate under Cirith Ungol, connecting the tower with
 * Torch Ungol, Shelobs lair. This side is the door in the tower. You can
 * climb over it and you can unbolt it from this side.
 *
 * /Mercade, 18 October 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/lair/lairgate_base";

#include "/d/Gondor/defs.h"

#undef OTHER_ROOM
#define OTHER_ROOM LAIR_DIR + "tunnel8"

void create_door()
{
    ::create_door();

    set_lock_command( "bolt" );
    set_unlock_command( "unbolt" );
    set_lock_desc( "It is a large, iron bolt, strong enough to withstand "+
        "any preasures on the door. Behind the door there must be"+
        "something very strong that the orcs here want to keep on the other"+
        "side of of the door.\n" );
    set_open_desc( "An open gate, leading west.\n" );
    set_closed_desc( "A closed gate, leading west.\n" );
    set_pass_command( ({ "west", "w" }) );
    set_door_desc( "The gate is made of stone and it looks very strong.\n" );
    set_fail_pass( "As you try to walk west, you bump against the great "+
        "arched gate.\n" );
    set_open_mess( ({
        "opens the strong gate in the west wall.",
        "Suddenly the strong gate in the east wall opens.\n" }) );
    set_fail_open( ({
        "The strong gate in the west wall is already open.\n",
        "The strong gate in the west wall is bolted.\n" }) );
    set_close_mess( ({
        "closes the strong gate in the west wall.",
        "Suddenly the strong gate in the east wall closes.\n" }) );
    set_lock_mess( ({
        "locks the strong gate in the west wall.",
        "Suddenly you hear a sound as if the strong gate in the east "+
            " wall is being bolted.\n" }) );
    set_unlock_mess( ({
        "unlocks the strong gate in the west wall.",
        "Suddenly you hear a sound as if the strong gate in the east "+
        " wall is being unbolted.\n" }) );
    set_fail_lock( ({
        "The strong gate in the west wall is already bolted.\n" ,
        "The strong gate in the west wall cannot be bolted "+
        "for it is open.\n" }) );
    set_fail_close( "The strong gate in the west wall is already "+
        "closed.\n" );
    set_fail_unlock( "The strong gate in the west wall is not bolted.\n" );
    set_other_room( LAIR_DIR + "tunnel8" );
}
