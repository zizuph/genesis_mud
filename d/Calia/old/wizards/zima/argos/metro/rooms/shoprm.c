/*
** ARGOS - Metro - shop inventory room (inaccessible to mortals)
**
** History
** Date      Coder      Action
** -------- ----------- --------------------------
** 3/3/95   Zima        Created
**
*/
inherit "/lib/store_support";
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
 
#define HARDWARE_DIR  ROOM_DIR+"shop_inv/"
 
 
void create_room() {
   set_short("Inside the shop backroom");
   set_long(
      "Argos shop inventory room. Inaccessible to mortals.\n");
 
   add_exit(ROOM_DIR+"shop","out",0);
   add_prop(ROOM_I_INSIDE, 1);
   (clone_object(ARMOUR_DIR+"cztunic"))->move(THIS);
   (clone_object(ARMOUR_DIR+"czcloak"))->move(THIS);
}
 
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
