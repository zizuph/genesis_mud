/* ARGOS - SWTERR - Hardware Room of the travelling salesman (in wagon)
**                  Not accessible to players.
**
** History:
** Date      Coder      Action
** --------- ---------- ---------------------------
** 9/10/95   Zima       Created
*/
inherit "/lib/store_support";
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
 
object axe=0;
object tunic=0;
 
void create_room() {
    set_short("Inside the merchant's wagon");
    set_long(
        "This store-room is used to store all items that are for " +
        "sale by the merchant in the SWTERR of Argos.\n");
    add_prop(ROOM_I_INSIDE, 1);
    axe=clone_object(WEAPON_DIR+"axe");
    axe->move(THIS);
    tunic = clone_object(ARMOUR_DIR+"wmtunic");
    tunic->move(THIS);
    add_exit(ROOM_DIR+"r22","out");
}
public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);
   store_update(ob);
}

