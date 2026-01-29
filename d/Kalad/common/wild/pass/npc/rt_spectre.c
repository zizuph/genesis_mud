/* 
 * /d/Kalad/common/wild/pass/npc/rt_spectre.c
 * Purpose    : A spectral warrior
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
   set_name("spectre");
   set_race_name("spectre");
   set_adj("chilling");
   add_adj("horrific");
   set_long("A semi-transparent being of a shockingly white pallor, "+
      "dressed in tattered robes with its hood pulled back. Its face was "+
      "once human, but it now appears as nothing more than a mask filled with "+
      "hatred and loathing.\n");
   set_alignment(-1000);
   set_knight_prestige(1000);
   set_aggressive(1);
   set_stats(({100,100,100,75,75,100}));
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_AWARENESS,100);
   add_prop(LIVE_I_SEE_DARK,100);
   add_prop(LIVE_I_SEE_INVIS,1);
   add_prop(LIVE_I_UNDEAD,75);
   add_prop(LIVE_I_NO_CORPSE,1);
   set_act_time(3);
   add_act("moan");
   add_act("groan");
   add_act("emote turns its undead eyes upon you, burrowing into your soul.");
   set_cact_time(3);
   add_cact("say You will join me in eternal undeath!");
   add_cact("emote grins with unholy desire for your soul.");
   set_attack_unarmed(A_TOUCH, 30, 30, W_IMPALE, 100, "chilling touch");
   set_hitloc_unarmed(H_HEAD, ({ 30, 30, 30 }), 15, "spectral head");
   set_hitloc_unarmed(H_BODY, ({ 40, 40, 40 }), 45, "spectral body");
   set_hitloc_unarmed(H_LARM, ({ 30, 30, 30 }), 10, "spectral left arm");
   set_hitloc_unarmed(H_RARM, ({ 30, 30, 30 }), 10, "spectral right arm");
   set_hitloc_unarmed(H_LEGS, ({ 35, 35, 35 }), 20, "spectral legs");
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if(aid == A_TOUCH)
      {
      tell_object(enemy, "The chilling horrific spectre touches you! You feel "+
         "your lifeforce being drained away!\n");
      {
         enemy -> heal_hp(-100);
      }
   }
   return 0;
}
