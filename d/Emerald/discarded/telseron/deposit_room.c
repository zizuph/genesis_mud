/*
 * Deposit for Telseron
 * Updated by Finwe September 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    object deposit;
 
    set_short("Gnome deposit");
    set_long( "This is a small room, upstairs from the main bank " +
        "office. The only exit is downstairs into the main " +
        "bank.\n" );
 
    add_exit(TOWNSHIP_DIR + "bank", "down");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    deposit = clone_object("/d/Genesis/obj/deposit");
    deposit->move(this_object());
}
