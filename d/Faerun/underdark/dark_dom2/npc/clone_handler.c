/*
 * Clone handler for Underdark NPCs
 * -- Finwe, July 2006
 */

inherit "/d/Faerun/std/clone_handler";
 
#include "/d/Faerun/defs.h"
#include "defs.h"
 
void
create_clone_handler()
{
    set_default_area(ROOM_DIR);
//    add_clone(NPC_DIR + "illithid", 1, 5);
//    add_clone(NPC_DIR + "svirf",    2, 15);
    add_clone(NPC_DIR + "skeleton",    15, 15);
    add_clone(NPC_DIR + "necro",    1, 5);
   
/*    add_excluded_destination(TUN_DIR + "basic_room");
    add_excluded_destination(TUN_DIR + "cv01");
    add_excluded_destination(TUN_DIR + "cv02");
    add_excluded_destination(TUN_DIR + "cv03");
    add_excluded_destination(TUN_DIR + "cv04");
    add_excluded_destination(TUN_DIR + "cv05");
    add_excluded_destination(TUN_DIR + "cv06");
    add_excluded_destination(TUN_DIR + "falling");
*/
    set_clone_handler_id("Underdark Clone Handler");
} 
