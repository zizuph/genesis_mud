/*
 * /d/Gondor/mordor/obj/undergate_tower.c
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
    add_name( "gate");
    add_adj( ({ "strong", "oak" }) );

    set_open_command( "open" );
    set_close_command( "close" );
    set_lock_command( "bolt" );
    set_unlock_command( "unbolt" );

    set_open( 0 );
    set_locked( 1 );

    add_item( ({ "band", "bands", "iron band", "iron bands" }),
        "The iron bands are fastened to the door to make it stronger "+
        "than it already is.\n" );
    add_item("oak",
        "The gate is made of solid oak, which makes the door very " +
        "strong. It looks much too tough to bash.\n" );

    set_lock_name( ({ "iron bolt", "bolt" }) );
    set_lock_desc( "It is a large, iron bolt, strong enough to withstand "+
        "any preasures on the door. Behind the door there must be "+
        "something very strong that the orcs here want to keep on the "+
        "other side of the door.\n" );

    set_other_room( LAIR_DIR+ "tunnel16" );
    set_door_id( "oak gate" );
    set_door_name( ({ "gate" , "door" }) );
    set_open_desc( "An open gate, leading west.\n" );
    set_closed_desc( "A closed gate, leading west.\n" );
    set_pass_command( ({ "west", "w" }) );
    set_door_desc( "The gate is made of solid oak and it looks very " +
        "strong. It is secured with iron bands. On this side of the gate "+
        "you see an iron bolt.\n" );
    set_fail_pass( "As you try to walk west, you bump against the great "+
        "arched gate.\n" );
    set_open_mess( ({
        "opens the strong gate in the west wall.",
        "Suddenly the strong gate in the east wall opens.\n" }) );
    set_fail_open( ({
        "The strong gate in the west wall is already open.\n",
        "The strong gate in the west wall is locked.\n" }) );
    set_close_mess( ({
        "closes the strong gate in the west wall.",
        "Suddenly the strong gate in the east wall closes.\n" }) );
    set_lock_mess( ({
        "locks the strong gate in the west wall.",
        "Suddenly you hear a sound as if the strong gate in the east "+
        "wall is being locked.\n" }) );
    set_unlock_mess( ({
        "unlocks the strong gate in the west wall.",
        "Suddenly you hear a sound as if the strong gate in the east "+
        "wall is being unlocked.\n" }) );
    set_fail_lock( ({
        "The strong gate in the west wall is already locked.\n" ,
        "The strong gate in the west wall cannot be locked "+
        "for it is open.\n" }) );
    set_fail_close( "The strong gate in the west wall is already "+
        "closed.\n" );
    set_fail_unlock( "The strong gate in the west wall is not locked.\n" );
    set_long( query_door_desc() );
}

