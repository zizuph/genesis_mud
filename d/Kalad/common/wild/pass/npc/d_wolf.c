/* 
 * /d/Kalad/common/wild/pass/npc/d_wolf.c
 * Purpose    : A desert wolf
 * Located    : /d/Kalad/common/wild/pass/desert/rock
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define A_LPAW 1
#define A_RPAW 2
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("wolf");
   set_race_name("wolf");
   set_adj("savage");
   set_short("savage wolf");
   set_pshort("savage wolves");
   set_long("A large beast with dirty brown fur and a maw bristling "+
      "with sharp canine teeth, it is one of the many wolves that roam "+
      "around in packs here in the Great Kalad Waste. Alone it is dangerous, "+
      "in a pack it is absolutely dangerous.\n");
   set_gender(G_NEUTER);
   set_stats(({50,50,50,25,25,60}));
   set_skill(SS_DEFENCE,30);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_WEIGHT,55000);
   add_prop(CONT_I_VOLUME,55000);
   add_prop(OBJ_I_NO_INS, 1);
   set_aggressive(1);
   set_random_move(10);
   set_act_time(3);
   add_act("snarl all");
   add_act("growl all");
   add_act("emote emits a long howling sound.");
   set_cact_time(3);
   add_cact("emote howls long and loud.");
   set_attack_unarmed(A_BITE, 20, 20, W_IMPALE, 10, "jaws");
   set_attack_unarmed(A_LPAW,   25, 15, W_SLASH, 45, "left paw");
   set_attack_unarmed(A_RPAW,   25, 15, W_SLASH, 45, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 10, 15, 15 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 15, 20 }), 60, "body");
   set_hitloc_unarmed(H_LEGS, ({ 10, 10, 10 }), 20, "legs");
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote snarls angrily!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
