 
/*
 * Coders : Mercade and Maniac and Zima
 *
 * This is the store-room of the hardware shop of the
 * crystalline palace.  Adapted from the original code
 * by Mercade for the dwarven race guild store.
 *
 * Created 2/2/94 by Maniac
 * Copied  2/14/94 by Zima
 * Revision history:
 */
 
inherit "/lib/store_support";
inherit "/std/room";
 
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
 
#define HARDWARE_SHOP	(ROOM_DIR+"tentcourt")
#define HARDWARE_DIR     ROOM_DIR + "wagon_wares/"
 
 
/*
 * Prototype
 */
object axe=0;
object tunic=0;
 
void
create_room()
{
    set_short("Inside the merchant's wagon");
    set_long(break_string( 
            "This store-room is used to store all items that are for " + 
        "sale by the merchant in the SWTERR of Argos.\n",70));
 
    add_exit(HARDWARE_SHOP, "out");
 
    add_prop(ROOM_I_INSIDE, 1);
   axe=clone_object(WEAPON_DIR+"gsword");
    axe->move(THIS);
   tunic = clone_object(ARMOUR_DIR+"vmtunic");
    tunic->move(THIS);
 
 
}
