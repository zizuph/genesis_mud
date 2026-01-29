/* 
 * Tobin, the Shop keeper at Smiths Guild 
 *
 * Fixed Tobin to sell wood poles
 * Sells strips of leather
 * No longer sells steel bars
 * -- Finwe, June 2001
 * 
 * Set seller to sell max number of leathers
 * -- Finwe, July 2001
 */


inherit "/sys/global/money";
inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "../smiths.h"

#define NECKLACE SMITHSDIR_OBJ+"npc_neck"

int max_leathers;
void wield_me();

void
create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"tobin","smiths_guild_keeper","keeper"}));
   set_title("Ironshoe, shopkeeper of the Smiths Guild");
   set_race_name("dwarf");
   set_adj("old");
   set_long("Tobin Ironshoe is the shopkeeper in the Smiths Guild.\n");

             /* STR  DEX CON INT WIS DIS */
   set_stats(({ 90, 50, 100, 50, 70, 90 })); 

   add_ask(({"buy","steel bar","steel bars"}),QCTNAME(TO)+" says to you: "+
      " That was lucky, I have just bought a large amount of steel bars. You"+
      " can <pay>"+
      STEEL_COST+" copper coins for a steel bar.\n");
   add_ask(({"pole","wooden pole","wooden poles"}),QCTNAME(TO)+
      " says to you: "+
      " That was lucky, I have all the wooden poles you want. You"+
      " can <pay>"+
      WOOD_COST+" copper coins for a wooden pole.\n");

   set_alignment(250);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_DEFENCE,80);

   set_alarm(2.0, 0.0, &wield_me());
//   max_leathers = random(50)+100;
   max_leathers = 3;
}



init_living()
{
   add_action("pay", "pay");
   ::init_living();     
}

void
wield_me() {
   object neck;

   seteuid(getuid(this_object()));

   neck = clone_object(NECKLACE);
   neck->set_short("copper necklace");
   neck->set_adj("copper");
   neck->move(this_object());
   command("wear necklace");
}

int
add_introduced(string name) 
{
   set_alarm(1.0, 0.0, &command("introduce me to " + name));
   return 1;
}

int
pay(string str) {
   object ob;

   if (str=="for leather") 
   {
   write(max_leathers);
    if (max_leathers<=0)
    {
        write("I am out of leathers now. You will have to get " +
            "some on your own.\n");
        return 1;
    }
      
      if (!take_money(TP,LEATHER_COST)) {
         TO->command("say You don't have enough"+
            " money to pay me. Are you trying to cheat me on purpose?");
         return 1;
      }
      else 
      {
         ob=clone_object(SMITHSDIR_OBJ+ "sm_leath");
         if (ob->move(TP)!=0)
         {
            TO->command("say It seems you cannot carry the leather you've"+
               " bought. I will drop it on the floor for you.");
            ob->move(ENV(TP));
         }
         else TP->catch_msg("Tobin hands you a strip of leather.\n");

         TO->command("say It is a pleasure dealing with you.\nJust come"+
            " back if you need more strips of leather.");
            max_leathers = max_leathers - 1;
         return 1;
      }
   }

   if (str=="for wooden pole") {
      if (!take_money(TP,WOOD_COST)) {
         TO->command("say You don't have enough"+
            " money to pay me. Are you trying to cheat me on purpose?");
         return 1;
      }
      else {
         ob=clone_object(SMITHSDIR_OBJ+ "sm_wood");
         if (ob->move(TP)!=0) {
            TO->command("say It seems you cannot carry the pole you've"+
               " bought. I will drop it on the floor for you.");
            ob->move(ENV(TP));
         }
         else TP->catch_msg("Tobin hands you a wooden pole.\n");

         TO->command("say It is a pleasure dealing with you.\nJust come"+
            " back if you need more poles.");
         return 1;
      }
   }

        if(str !="for wooden pole" || str != "for steel bar")
                notify_fail("Try with 'pay for wooden pole', or 'pay for leather'.\n");
                return 0;
}
