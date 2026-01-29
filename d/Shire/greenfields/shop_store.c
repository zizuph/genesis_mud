/*
 *   The storage room of the Greenfields drugstore
 */

inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room() {
   set_short("Drugstore storage room");
   set_long(break_string(
      "You have entered the dusty storage room of the Tools and Supplies "
    + "shop. This is where the shopkeeper keeps all his items that "
    + "are for sale in the store. "
    + "You better leave the stuff here alone, or else the shopkeeper "
    + "will be upset with you.\n",70));

   add_exit("/d/Shire/greenfields/shop","south");

   add_prop(ROOM_I_INSIDE, 1);

   max_items = 50;
}

