/*
 *   The storage room of the Greenholm drugstore
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

create_room() {
   set_short("Drugstore storage room");
   set_long(break_string(
      "You have entered the dusty storage room of the Tools and Supplies "
    + "shop. This is where the shopkeeper keeps all his items that "
    + "are for sale in the store. "
    + "You better leave the stuff here alone, or else the shopkeeper "
    + "will be upset with you.\n",70));

   add_exit("/d/Shire/eastroad/village/greenholm/shop","south");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
   max_items = 50;
  reset_room();
}

reset_room() {
  if (!present("shoptorch"))
    clone_object(STAND_OBJ + "shoptorch")->move(this_object());
  if (!present("shopsword"))
    clone_object(STAND_WEAPON + "shopsword")->move(this_object());
  if (!present("sack"))
    clone_object(STAND_OBJ + "sack")->move(this_object());
  if (!present("_ink_"))
    clone_object(STAND_OBJ + "ink")->move(this_object());
  if (!present("_quill_"))
    clone_object(STAND_OBJ + "quill")->move(this_object());
  if (!present("_piece_of_paper_"))
    clone_object(STAND_OBJ + "paper")->move(this_object());
  if (!present("shire_bag"))
    clone_object(STAND_OBJ + "herbbag")->move(this_object());
}
