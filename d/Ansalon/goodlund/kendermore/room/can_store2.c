/*
* The storeroom Jenna's Candle Store.
*/

inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include "/sys/stdproperties.h"
#include "/d/Ansalon/common/defs.h"

#define CANDLE KOBJ + "candle"

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}

create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");
   
   add_exit(KROOM + "can_store1","north");
   
   INSIDE;  /* This is an inside room */
   reset_room();
}

reset_room()
{
   object ob;
   seteuid(getuid(TO));
   if (!P(CANDLE, TO))
      {
      ob = clone_object(CANDLE);
      ob->add_name(CANDLE);
      ob->move(TO);
      ob = clone_object(CANDLE);
      ob->add_name(CANDLE);
      ob->move(TO);
      ob = clone_object(CANDLE);
      ob->add_name(CANDLE);
      ob->move(TO);
      ob = clone_object(CANDLE);
      ob->add_name(CANDLE);
      ob->move(TO);
      ob = clone_object(CANDLE);
      ob->add_name(CANDLE);
      ob->move(TO);
      }
}
