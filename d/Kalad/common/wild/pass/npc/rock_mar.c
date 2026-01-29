/* 
 * /d/Kalad/common/wild/pass/npc/rock_mar.c
 * Purpose    : A rock marauder
 * Located    : /d/Kalad/common/wild/pass/desert/rock/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_LFIST 1
#define A_RFIST 2
#define H_HEAD 0
#define H_BODY 1
#define H_LARM 2
#define H_RARM 3
#define H_LEGS 4
/* The rock marauder, infamous dweller of the rock plains in the Kalad
desert. */
/* by Antharanos */
create_monster()
{
   set_name("marauder");
   set_race_name("marauder");
   set_adj("rock");
   set_long("A vaguely humanoid-shaped mass of wrinkled flesh. Its "+
      "strangely colored skin tone matches the hue and texture of the surrounding "+
      "rocky plains, making it advantageously camouflaged. Its repulsive "+
      "head is dominated by a large, circular mouth filled with needle-sharp "+
      "rows of teeth.\n");
   set_stats(({70,60,70,40,40,80}));
   set_gender(G_NEUTER);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_AWARENESS,50);
   set_attack_unarmed(A_MOUTH, 30, 30, W_IMPALE, 10, "spike-filled mouth");
   set_attack_unarmed(A_LFIST, 25, 25, W_BLUDGEON, 45, "wrinkled left fist");
   set_attack_unarmed(A_RFIST, 25, 25, W_BLUDGEON, 45, "wrinkled right fist");
   set_hitloc_unarmed(H_HEAD, ({ 20, 20, 20 }), 15, "wrinkled head");
   set_hitloc_unarmed(H_BODY, ({ 30, 30, 30 }), 45, "wrinkled body");
   set_hitloc_unarmed(H_LARM, ({ 25, 25, 25 }), 10, "wrinkled left arm");
   set_hitloc_unarmed(H_RARM, ({ 25, 25, 25 }), 10, "wrinkled right arm");
   set_hitloc_unarmed(H_LEGS, ({ 25, 25, 25 }), 20, "wrinkled legs");
   set_act_time(3);
   add_act("emote twists its suckered mouth into a frightening expression.");
   add_act("emote moves, its flesh rippling strangely.");
   set_cact_time(3);
   add_cact("emote darts its tongue out at you.");
   set_random_move(10);
   set_aggressive(1);
   add_leftover("/d/Kalad/common/wild/pass/obj/mar_sac","sac",1,"",1,1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
}
int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
   if(aid == A_MOUTH)
      {
      tell_object(enemy,"The rock marauder's suckered mouth rips into you!\n");
      {
         enemy -> heal_hp(-50);
         if(enemy->query_hp() <= 500)
            {
            enemy->command("$panic");
            enemy->command("$options wimpy brave");
         }
      }
   }
   return 0;
}
