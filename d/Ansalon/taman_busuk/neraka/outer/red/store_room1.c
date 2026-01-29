/*
* the storeroom for Lute's Loot, in the red quarter.
*/

inherit "/std/room";
inherit "/lib/store_support";

#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/sys/stdproperties.h"
#include "/d/Ansalon/common/defs.h"

#define TORCH "solace_shop_torch"

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}

void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");
   
   add_exit(NOUTER+"red/store1","north");
   
   INSIDE;  /* This is an inside room */
   reset_room();
}

reset_room()
{
   object ob;
   seteuid(getuid(TO));
   if (!P(TORCH, TO))
      {
      ob = clone_object("/d/Krynn/solace/village/obj/torch");
      ob->add_name(TORCH);
      ob->move(TO);
      ob = clone_object("/d/Krynn/solace/village/obj/torch");
      ob->add_name(TORCH);
      ob->move(TO);
      ob = clone_object("/d/Krynn/solace/village/obj/torch");
      ob->add_name(TORCH);
      ob->move(TO);
   }
}
