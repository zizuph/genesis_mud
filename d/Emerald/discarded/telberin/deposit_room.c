/*
 * Deposit for Telberon
 * By Finwe
 * January 1996
 */
 
inherit "/std/room";
 
#include "default.h"
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    object deposit;
 
    set_short("Strong Room");
    set_long( "   This is a small room, upstairs from the main bank " +
        "office. The only exit is downstairs into the main " +
        "bank.\n\n" );
 
    add_exit(THIS_DIR + "bank", "down");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    deposit = clone_object("/d/Genesis/obj/deposit");
    deposit->move(this_object());
}
