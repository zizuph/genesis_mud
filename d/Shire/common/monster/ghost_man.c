/*
 *  A common guard, for guarding the Hin Warrior area
 */

inherit "/std/monster";
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

create_monster()
{
   if (!IS_CLONE)
      return;
   set_name("ghost");
   set_adj("misty");
   set_race_name("ghost");
   set_gender(G_MALE);
   set_long(break_string(
      "This is the ghost of a man long since dead. He seems to be doing "
    + "the same things now that he did when he was alive.\n",70));

   default_config_npc();
   set_stats(({ 30, 30, 30, 30, 30, 30 }));
   set_hp(500);

   set_skill(SS_UNARM_COMBAT,30);
   set_skill(SS_WEP_SWORD,30);
   set_skill(SS_WEP_AXE,30);
   set_skill(SS_WEP_KNIFE,30);
   set_skill(SS_DEFENCE,30);
   set_skill(SS_PARRY,30);

   set_aggressive(0);
   set_attack_chance(0);

   add_prop(CONT_I_WEIGHT, 0);   /* 0 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
}

/* For the solamnic Knights. */

query_knight_prestige() { return(100); } /* not evil but still a ghost */
   
query_not_attack_me(object attacker,int att_id) {

  object weapon;
  command("say query_not_attack_me");
  weapon = attacker->query_weapon(att_id);
  set_this_player(attacker);

  write(weapon);
  write(att_id);

  if(!weapon) {
    if(!att_id) {
      command("say with what");
      return 1;
    }
      switch(att_id) {
     case TS_LWEAPON:
      attacker->catch_msg("Your left arm passes right through the ghost\n");
      say(QCTNAME(attacker) + 
	  "s  left arm passes right through the ghost\n"); 
      break;
    case TS_RWEAPON:
      attacker->catch_msg("Your right arm passes right through the ghost\n");
      say(QCTNAME(attacker) + 
	  "s  right arm passes right through the ghost\n");
      break;
    case TS_RFOOT:
      attacker->catch_msg("Your right foot passes right through the ghost\n");
      say(QCTNAME(attacker) + 
	  "s  right foot passes right through the ghost\n");
      break;
    case TS_LFOOT:
      attacker->catch_msg("Your left foot passes right through the ghost\n");
      say(QCTNAME(attacker) + 
	  "s  left foot passes right through the ghost\n");
      break;
    }
    return 1;
  }
  if(weapon->query_prop(MAGIC_AM_ID_INFO)) {
    command("say magic in work");
     return 0;
  }

  say("The " + weapon->short() + " passes right through the ghost.\n");
  attacker->catch_msg("The " + weapon->short() +
		      " passes right through the ghost.\n");
  return 1;

}

