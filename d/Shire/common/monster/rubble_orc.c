/*
 *  A sleeping orc guard
 */

inherit "/std/monster";

#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_monster()
{

   if (!IS_CLONE)
      return;

   set_name("orc");
   set_adj(({"looting","small"}));
   set_race_name("orc"); 
   set_long("This orc is out looting the streets of this city.\n"
	    + "He seems quite busy.\n");

   add_prop(CONT_I_WEIGHT,87000);   /* 87  Kg */
   add_prop(CONT_I_HEIGHT,153);     /* 153 cm */

   set_stats(({ 20, 25, 22,19, 17, 18}));
   set_skill(SS_UNARM_COMBAT,25);
   set_skill(SS_WEP_SWORD,25);
   set_pick_up(75);

   set_aggressive(1);
   set_attack_chance(80);

   set_hp(1000); /* Heal fully */

   /* Actions */
   set_act_time(5);
   add_act("burp");
   add_act("fart");

   /* Combat actions */
   set_cact_time(5);
   add_cact("shout Help! I'm under attack!");

   add_prop(LIVE_I_NEVERKNOWN, 1); /* You never get to meet him */

   call_out("arm",0);

}

arm() {

  seteuid(getuid());

  clone_object(STAND_WEAPON + "orc_scimitar")->move(this_object());
  command("wield " + "scimitar");

}

/* For the solamnic Knights */

query_knight_prestige() { return(55); }
