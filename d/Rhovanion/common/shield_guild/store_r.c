#pragma save_binary

inherit "/std/room";
inherit "/lib/store_support";
#include "guild.h"
#include <wa_types.h>

void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(THIS_DIR + "store_sc", "west");
   add_exit(THIS_DIR + "store_h", "east");
   /* Make sure the other stores are loaded */
   seteuid(getuid());
   (THIS_DIR + "store_sc")->apa();
   (THIS_DIR + "store_h")->apa();
   set_max_values(13, 5);
}

public void
enter_inv(object ob, object from)
{
  int wep = (function_exists("create_object", ob) == "/std/weapon");
  int arm = (function_exists("create_object", ob) == "/std/armour");

  if(wep && (ob->query_wt() == W_CLUB))
  {
    ob->move(THIS_DIR + "store_sc");
    return;
  }
  if(arm && (ob->query_at() == A_SHIELD))
  {
    ob->move(THIS_DIR + "store_sc");
    return;
  }
  if(!(wep || arm || living(ob)))
  {
    ob->move(THIS_DIR + "store_h");
    return;
  }

  ::enter_inv(ob, from);
  store_update(ob);
}
