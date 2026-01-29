#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";
#include "../guild.h"
#include <wa_types.h>

void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(AA_DIR + "rooms/store_sc", "west");
   add_exit(AA_DIR + "rooms/store_h", "east");
   /* Make sure the other stores are loaded */
   seteuid(getuid());
   (AA_DIR + "rooms/store_sc")->apa();
   (AA_DIR + "rooms/store_h")->apa();
   set_max_values(13, 5);
}

public void
enter_inv(object ob, object from)
{
  int wep = (function_exists("create_object", ob) == "/std/weapon");
  int arm = (function_exists("create_object", ob) == "/std/armour");

  if(wep && (ob->query_wt() == W_CLUB))
  {
    ob->move(AA_DIR + "rooms/store_sc");
    return;
  }
  if(arm && (ob->query_at() == A_SHIELD))
  {
    ob->move(AA_DIR + "rooms/store_sc");
    return;
  }
  if(!(wep || arm || living(ob)))
  {
    ob->move(AA_DIR + "rooms/store_h");
    return;
  }

  ::enter_inv(ob, from);
  store_update(ob);
}
