#pragma strict_types

inherit "/std/monster";

#include <macros.h>

#define BASKET_OB "/d/Shire/bree/obj/basket"
#define APPLE_OB "/d/Shire/bree/food/apple"

public void
create_monster()
{
   set_name("woman");
   set_long("It's a woman. Give her the freaking basket.\n");
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

public void
check_object(object ob, object from)
{
   int sz;
   object *inv;

   if(MASTER_OB(ob) != BASKET_OB)
   {
      command("say I don't want " + ob->short() + "!");
      ob->move(from, 1);
      from->catch_tell("The woman gives " + ob->short() + " back.\n");
      return;
   }

   inv = all_inventory(ob);
   sz = sizeof(inv);
   inv = filter(inv, &operator(==)(APPLE_OB) @ &function_exists("create_food"));

   if(sz != sizeof(inv))
   {
      command("say I don't want all of this crap!");
      ob->move(from, 1);
      from->catch_tell("The woman gives " + ob->short() + " back.\n");
      return;
   }


   if(sz > 0)
   {
      command("say Thanks for the apples!");
   } 
   else 
   {
      command("say Thanks for the effort, but I need more apples. you didn't give me the 10 apples I asked for.");
      ob->move(from, 1);
      from->catch_tell("The woman gives " + ob->short() + " back.\n");

   }
}

public void
enter_inv(object ob, object from)
{
   set_alarm(1.0, 0.0, &check_object(ob, from));
}
