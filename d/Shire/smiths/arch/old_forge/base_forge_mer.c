   /* The merchant of the smiths. he sells everything for the smiths.*/


#pragma save_binary;

inherit "/sys/global/money";
inherit "/std/monster";
inherit "/std/act/chat";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"

#define WEP         SMITHSDIR_OBJ+"bo_axe"
#define BO_NECKLACE SMITHSDIR_OBJ+"npc_neck"
#define NECKLACE    SMITHSDIR+"necklace"

//int give();
void wield_me();
void equipped();
int pay(string str);

object item, giver;
int    check_on=0;

void
create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({FORGE_MERCHANT_NAME,"merchant"}));
   add_name(FORGE_MERCHANT_RACE);
   set_race_name(FORGE_MERCHANT_RACE);
   set_adj(FORGE_MERCHANT_ADJ1);
   set_adj(FORGE_MERCHANT_ADJ2);
   set_long("This is the merchant for Imladris.\n");

             /* STR  DEX  CON INT WIS DIS */
   set_stats(({ 210, 210, 210, 90, 90, 100 })); 

   set_default_answer(QCTNAME(TO)+" tells you: For more " +
       "information, visit the Smiths guild in Bree.\n");
   add_ask(({"smiths"}), QCTNAME(TO)+" tells you: The Smiths " +
       "are a wonderful guild. Their guildhouse is in Bree, " +
       "but we have permitted them to use our forge here as needed.\n");
   add_ask(({"join","membership"}), QCTNAME(TO)+" tells you: If you want to"+
      " join then you, you will have to travel to Bree for more information.\n");
   add_ask(({"buy","iron bar","iron bars"}),QCTNAME(TO)+" tells you: Okay,"+
      " you can pay me "+IRON_COST+" copper coins and I will give you the iron bar.\n");
   add_ask(({"items","forging items","making items"}),
      QCTNAME(TO)+" tells you: Smiths can make swords, axes, maces,"+
      " knives, necklace, helmets and armours. Some weapons can be made"+
      " for both singlehanded and twohanded use.\n");
   add_ask(({"forging"}),
      QCTNAME(TO)+" tells you: In order to forge an item you " +
       "need at least some metal, and maybe some leather and and wood.\n");
   add_ask(({"forge room","forges"}),
      QCTNAME(TO)+" tells you: Besides forging you can melt and " +
       "polish items in the forge.\n");
   add_ask(({"iron","steel","blue steel","high steel"}),
      QCTNAME(TO)+" tells you: That is a very useful metal for forging.\n");
      
   set_chat_time(30);
   add_chat("The Smiths guild is very old and highly respected.");  
   add_chat("No smith has yet bested the abilities of the dwarves of old"+
      " when it comes to making weapons.");
   add_chat("I can sell you iron bars, wood, or leathers for forging.");

   set_alignment(100);
   set_skill(SS_WEP_AXE,100);
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,80);

//   remove_prop(NPC_M_NO_ACCEPT_GIVE);

   set_alarm(1.0, 0.0, &wield_me());
}

void
init_living()
{
   ::init_living();
   add_action("pay", "pay");
}

/*
void
enter_inv(object obj,object from) {
   ::enter_inv(obj,from);

   item=obj;
   giver=from;
   set_alarm(1.0, 0.0, give);
}
*/
void
wield_me() {
   object wep,neck;

   seteuid(getuid(this_object()));

   wep = clone_object(WEP);
   wep->move(this_object());
   command("wield axe");
   neck = clone_object(BO_NECKLACE);
   neck->set_short("gem studded mithril necklace");
   neck->set_adj("mithril");
   neck->set_adj("gem studded");
   neck->move(this_object());
   command("wear necklace");

   set_alarm(3.0, 0.0, equipped);
}

void
equipped() 
{
   check_on=1;
}

int
add_introduced(string name) 
{
   set_alarm(1.0, 0.0, &command("introduce me to " + name));
   return 1;
}

/* bores is paid in order to get an iron bar
*/

int
pay(string str) {
   object ob;
// Iron bar
   if ((str=="for iron bar")) 
   {
      if (!take_money(TP,IRON_COST))
      {
         TO->command("say You don't have enough"+
            " money to pay me. Come back when you have earned some more.");
         return 1;
      }
   else 
      {
         ob=clone_object(SMITHSDIR_OBJ+ "ir_bar");
         if (ob->move(TP)!=0) 
         {
            TO->command("say Hmm.. It seems you cannot even carry the"+
               " bar; You'll need quite a bit of luck being as weak as"+
               " you are. I will drop the bar on the floor for you.");
            ob->move(ENV(TP));
         }

         TO->command("say It is a pleasure dealing with you.\nGood luck"+
            " with the forging.");
         TP->catch_msg("You get an iron bar.\n");
         return 1;
       }
   }
// End of iron bar

// wooden Staff
   if ((str=="for wood")) 
   {
      if (!take_money(TP,WOOD_COST))
      {
         TO->command("say You don't have enough"+
            " money to pay me. Come back when you have earned some more.");
         return 1;
      }
   else 
      {
         ob=clone_object(SMITHSDIR_OBJ+ "sm_wood");
         if (ob->move(TP)!=0) 
         {
            TO->command("say Hmm...It seems you are too weak to " +
                "carry the wood. I shall drop it on the floor " +
                "for you to pick up later.");
            ob->move(ENV(TP));
         }

         TO->command("say It is a pleasure dealing with you.\nGood luck"+
            " with the forging.");
         TP->catch_msg("You get a piece of wood.\n");
         return 1;
       }
   }
// End of wooden staff


// leathers for sale
   if ((str=="for leather")) 
   {
      if (!take_money(TP,LEATHER_COST))
      {
         TO->command("say You don't have enough money to pay " +
             "me. Come back when you have earned some more.");
         return 1;
      }
   else 
      {
         ob=clone_object(SMITHSDIR_OBJ+ "sm_leath");
         if (ob->move(TP)!=0) 
         {
            TO->command("say Hmm...It seems you are too weak to " +
                "carry the leather. I'll drop it and you can " +
                "pick it up later.");
            ob->move(ENV(TP));
         }

         TO->command("say It is a pleasure dealing with you.\nGood luck"+
            " with the forging.");
         TP->catch_msg("You get a piece of leather.\n");
         return 1;
       }
   }
// End of leathers

    notify_fail("Pay for what? You can pay for iron bars, wood, " +
        "or leathers here.\n");
}
