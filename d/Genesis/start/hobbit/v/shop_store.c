/*
 *   The storage room of the Hobbiton drugstore
 */

#pragma save_binary

inherit "/std/room";
inherit "/lib/store_support";

#include "defs.h"
#include "/sys/stdproperties.h"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

create_room() {
   set_short("Drugstore storage room");
   set_long(break_string(
      "You have entered the dusty storage room of the drugstore. "
    + "This is where the owner of the store keeps all his items that "
    + "are for sale in the store. "
    + "You better leave the stuff here alone, or else the owner of "
    + "the store will probably upset with you.\n",70));

   add_exit(STAND_DIR + "shop","east");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
}