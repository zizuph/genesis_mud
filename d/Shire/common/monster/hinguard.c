/*
 *  A common guard, for guarding the Hin Warrior area
 */

inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "../defs.h"

create_monster()
{
   if (!IS_CLONE)
      return;
   set_name(({"hin warrior","warrior","guard"}));
   set_race_name("Hin Warrior guard"); 
   set_long(break_string(
      "The guard is not a hobbit, maybe it is a Bree man, hired for the job. "
    + "He looks very capable of doing his job.\n",70));

            /* STR DEX CON INT WIZ DIS */
   set_stats(({ 50, 40, 40, 40, 50, 50}));
   set_skill(SS_UNARM_COMBAT,37);
   set_skill(SS_WEP_SWORD,37);
   set_skill(SS_WEP_AXE,37);
   set_skill(SS_WEP_KNIFE,37);
   set_skill(SS_DEFENCE,37);
   set_skill(SS_PARRY,37);
   set_pick_up(75);

   set_aggressive(0);
   set_attack_chance(0);

   set_chat_time(5);
   add_chat("Good day, squire!");
   add_chat("Hail Shire!");
   add_chat("Did you already join the Shire-guild?");
   add_chat("Did you know that members of the Shire-guild are called Hin Warriors?");
   add_chat("Do not fear to ask the brotherhood for help should you be in trouble!");
   add_chat("Remember! True Hin Warriors only fight honorable fights!");
   add_chat("Do not disgrace our guild.");

   set_cchat_time(5);
   add_cchat("Have at you!");
   add_cchat("May you die quickly and painless!");

   add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CORPSE_S_RACE,"human");

    set_alarm(1.0,0.0,"arm");

}

arm() {
  object wep;
   seteuid(getuid(TO));
  wep = clone_object("/d/Shire/common/weapon/shortsword");
  wep->move(TO);
  command("wield shortsword");
}
