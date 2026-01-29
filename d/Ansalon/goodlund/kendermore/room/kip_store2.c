/*
* the store for the Palanthas shop.
*/

inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include "/sys/stdproperties.h"
#include "/d/Ansalon/common/defs.h"

#define VEST KOBJ + "vest"

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
   
   add_exit(KROOM + "kip_store1","north");
   
   INSIDE;  /* This is an inside room */
   reset_room();
}

reset_room()
{
   object ob;
   seteuid(getuid(TO));
   if (!P(VEST, TO))
      {
      ob = clone_object(VEST);
      ob->add_name(VEST);
      ob->move(TO);
      ob = clone_object(VEST);
      ob->add_name(VEST);
      ob->move(TO);
      ob = clone_object(VEST);
      ob->add_name(VEST);
      ob->move(TO);
      }
   if (!P("leggings", TO))
      ob = clone_object(KOBJ + "leggings")->move(TO);
      clone_object(KOBJ + "leggings")->move(TO);
      clone_object(KOBJ + "leggings")->move(TO); 
   if (!P("blouse", TO))
     {
      clone_object(KOBJ + "blouse")->move(TO);
      clone_object(KOBJ + "blouse")->move(TO);
      clone_object(KOBJ + "blouse")->move(TO);
     }
   if (!P("cape", TO))
     {
      clone_object(KOBJ + "cape")->move(TO);
      clone_object(KOBJ + "cape")->move(TO);
      clone_object(KOBJ + "cape")->move(TO);
     }
   if (!P("cloak", TO))
     {
      clone_object(KOBJ + "cloak")->move(TO);
      clone_object(KOBJ + "cloak")->move(TO);
      clone_object(KOBJ + "cloak")->move(TO);
     }
   if (!P("shirt", TO))
     {
      clone_object(KOBJ + "shirt")->move(TO);
      clone_object(KOBJ + "shirt")->move(TO);
      clone_object(KOBJ + "shirt")->move(TO);
     }
   if (!P("boots", TO))
     {
      clone_object(KOBJ + "boots")->move(TO);
      clone_object(KOBJ + "boots")->move(TO);
      clone_object(KOBJ + "boots")->move(TO);
     }
   if (!P("hat", TO))
     {
      clone_object(KOBJ + "hat")->move(TO);
      clone_object(KOBJ + "hat")->move(TO);
      clone_object(KOBJ + "hat")->move(TO);
     }
   }
