/* 
 * /d/Kalad/common/wild/pass/npc/rt_wight.c
 * Purpose    : A wight of ages
 * Located    : /d/Kalad/common/wild/pass/desert/sand/r*
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_TOUCH 0
#define H_HEAD 0
#define H_BODY 1
#define H_LARM 2
#define H_RARM 3
#define H_LEGS 4
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("wight");
   set_race_name("wight");
   set_adj("ghastly");
   set_long("It may once have been human, but now it is a nightmarish "+
      "creature with cruel, burning eyes set in mummified flesh over a "+
      "twisted skeleton with hands that end in sharp claws.\n");
   set_alignment(-750);
   set_knight_prestige(750);
   set_aggressive(1);
   set_stats(({75,75,75,50,50,75}));
   set_skill(SS_UNARM_COMBAT,75);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_DEFENCE,75);
   set_skill(SS_AWARENESS,75);
   add_prop(LIVE_I_SEE_DARK,100);
   add_prop(LIVE_I_SEE_INVIS,1);
   add_prop(LIVE_I_UNDEAD,50);
   set_act_time(3);
   add_act("growl all");
   add_act("snarl all");
   add_act("emote snarls with unholy rage at you.");
   set_cact_time(3);
   add_cact("growl all");
   add_cact("snarl all");
   add_cact("emote twists its face into a mask of utter hatred.");
   set_attack_unarmed(A_TOUCH, 25, 25, W_IMPALE, 100, "horrible touch");
   set_hitloc_unarmed(H_HEAD, ({ 25, 25, 25 }), 15, "mummified head");
   set_hitloc_unarmed(H_BODY, ({ 35, 35, 35 }), 45, "mummified body");
   set_hitloc_unarmed(H_LARM, ({ 25, 25, 25 }), 10, "mummified left arm");
   set_hitloc_unarmed(H_RARM, ({ 25, 25, 25 }), 10, "mummified right arm");
   set_hitloc_unarmed(H_LEGS, ({ 30, 30, 30 }), 20, "mummified legs");
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if(aid == A_TOUCH)
      {
      tell_object(enemy, "The ghastly wight touches you! You feel as if "+
         "your lifeforce is being drained away!\n");
      {
         enemy -> heal_hp(-50);
      }
   }
   return 0;
}
