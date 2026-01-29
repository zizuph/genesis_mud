/*
 * /d/Gondor/mordor/obj/undergate_lair.c
 *
 * This 'door' is the gate under Cirith Ungol, connecting the tower with
 * Torch Ungol, Shelobs lair. This side is the door in the tower.
 *
 * /Mercade, 23 September 1993
 *
 * Revision history:
 * 26.06.2002, Chmee, description bug removed
 */

inherit "/std/door";

#include "/d/Gondor/defs.h"

/*
 * Called to create the door.
 */
void create_door()
{
    add_name( "gate" );
    add_adj( ({ "strong", "oak" }) );

    set_open_command( "open" );
    set_close_command( "close" );

    set_open( 0 );
    set_locked( 1 );

    add_item( ({ "band", "bands", "iron band", "iron bands" }),
        "The iron bands are fastened to the door to make it stronger "+
        "than it already is.\n" );
    add_item( "oak",
        "The gate is made of solid oak, which makes the door very "+
        "strong. It looks much too tough to bash.\n" );

    set_lock_name( ({ "iron bolt", "bolt", "lock" }) );
    set_lock_desc( "You see no lock on this side of the gate.\n" );

    set_other_room( UNGOL_DIR+ "tower/west05" );
    set_door_id( "oak gate" );
    set_door_name( ({ "gate" , "door" }) );
    set_open_desc( "An open gate, leading east.\n" );
    set_closed_desc( "A closed gate, leading east.\n" );
    set_pass_command( ({ "east", "e" }) );
    set_door_desc( "The gate is made of solid oak and it looks very "+
        "strong. It is secured with iron bands.\n" );
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
    set_fail_close( "The strong gate in the east wall is already "+
        "closed.\n" );
    set_long( query_door_desc() );
}
