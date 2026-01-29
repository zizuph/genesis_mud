/**********************************************************************
 * - milligan.c                                                     - *
 * - NPC that will sell needed smith items for forging in Khal.     - *
 * - Created by Damaris@Genesis 02/2005                             - *
 * - Refactored, Tapakah, 07/2021
 **********************************************************************/

#pragma strict_types

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "npc.h"

inherit "/sys/global/money";
inherit BASE_NPC;

#define SMITHSDIR_OBJ "/d/Shire/guild/smiths/obj/"
#define IRON_COST     300
#define LEATHER_COST  300
#define WOOD_COST     300
#define NECKLACE      SMITHSDIR_OBJ + "npc_neck"

void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name(({"smith", "merchant", "shopkeep", "seller", "man","shopkeeper"}));
  set_adj(({"old", "stout"}));
  set_long("Milligan is an old stout man that has seen many "+
           "days gone by. It is obvious he is old but quite strong "+
           "still and even though his forge fires have died down he "+
           "still has the glint of a very strong and noble smith. He "+
           "rarely pumps a bellow but he still maintains his "+
           "love for the forge and now sells needed items to those "+
           "he finds worthy.\n");
  
  set_stats(({ 90, 50, 100, 50, 70, 90 })); 

  add_ask(({"steel bar","steel bars"}),QCTNAME(TO)+" says to you: "+
          "I do not sell steel bars.\n");
  add_ask(({"pole","wooden pole","wooden poles"}),QCTNAME(TO)+
          " says to you: "+
          " That was lucky, I have all the wooden poles you want. You"+
          " can <pay>"+
          WOOD_COST+" copper coins for a wooden pole.\n");
  
   set_alignment(250);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_DEFENCE,80);
}

void
init_living ()
{
   add_action("pay", "pay");
   ::init_living();     
}

void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/vest_hard_leather",
               "/d/Khalakhor/common/arm/belt" });
  ::arm_me();
  object neck = clone_object(NECKLACE);
  neck->set_short("copper necklace");
  neck->set_adj("copper");
  neck->move(this_object());
  command("wear all");

}

int
hook_return_intro_new (string str)
{
  command("greet " + str);
  command("introduce me to " + str);
}

int
hook_return_intro_bad (string str)
{
  command("say I remember you, and you'd be wise to " +
          "leave because of it.");
}

int
hook_return_intro_good (string str)
{
  command("chuckle");
  command("say The life of a merchant is a busy one, but " +
          capitalize(str) + ", I remember you. How can I help you?");
}
        
void
do_transaction (int cost, string goods, string str)
{
  object ob;
  if (!take_money(TP, cost)) {
    TO->command("say You don't have enough"+
                " money to pay me. Are you trying to cheat me on purpose?");
    return;
  }
  ob = clone_object(goods);
  if (ob->move(TP)) {
    command("say It seems you cannot carry the " + str +
            "you've bought. I will drop it right here for you.");
    ob->move(ENV(TO));
  }
  else
    TP->catch_msg("Milligan hands you a " + str + ".\n");

  command("say It is a pleasure dealing with you.\nJust come"+
          " back if you need more " + str +  "s.");
}

int
pay (string str) {
   object ob;

   setuid();
   seteuid(getuid());
   if (str == "for leather") {
     do_transaction(LEATHER_COST, SMITHSDIR_OBJ + "sm_leath", "leather");
   }
   else if (str == "for wooden pole" || str == "for wood") {
     do_transaction(WOOD_COST, SMITHSDIR_OBJ + "sm_wood", "wooden pole");
   }
   else if (str=="for iron bar" || str=="for iron" || str=="for bar") {
     do_transaction(IRON_COST, SMITHSDIR_OBJ + "ir_bar", "iron bar");
   }
   else {
     command("say try 'pay for wooden pole', 'pay for leather', " +
         "or 'pay for iron bar'");
     NF0("");
   }
   return 1;
}
