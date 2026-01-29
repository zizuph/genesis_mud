/* 
 * /d/Kalad/common/wild/pass/npc/chest_mimic.c
 * Purpose    : This is the npc that holds the feather for the oracle quest
 * Located    : /d/Kalad/common/wild/pass/desert/salt/l13
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_LID 0
#define H_BODY 1
#define H_LARM 2
#define H_RARM 3
#define H_LEGS 4
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("chest");
   add_name("mimic");
   add_name("chest mimic");
   add_name("golden chest");
   add_name("chest");
   set_race_name("mimic");
   set_adj("chest");
   set_short("golden chest");
   set_long("For the life of you, this thing looks like a golden chest "+
      "that has sprouted legs, two arms and a tooth-filled maw where its "+
      "cover should be!\n");
   set_stats(({75,85,75,15,15,80}));
   set_gender(G_NEUTER);
   set_skill(SS_UNARM_COMBAT,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_AWARENESS,30);
   set_aggressive(1);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_WEIGHT,25000);
   add_prop(CONT_I_VOLUME,25000);
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(OBJ_I_NO_INS,1);
   set_act_time(3);
   add_act("growl");
   add_act("emote snarls.");
   set_cact_time(3);
   add_cact("snarl all");
   set_attack_unarmed(A_BITE, 35, 35, W_IMPALE, 40, "toothed maw");
   set_attack_unarmed(A_LCLAW, 30, 30, W_SLASH, 30, "left claw");
   set_attack_unarmed(A_RCLAW, 30, 30, W_SLASH, 30, "right claw");
   set_hitloc_unarmed(H_LID, ({ 30, 30, 30 }), 20, "lid");
   set_hitloc_unarmed(H_BODY, ({ 25, 25, 25 }), 40, "body");
   set_hitloc_unarmed(H_LARM, ({ 20, 20, 20 }), 10, "left arm");
   set_hitloc_unarmed(H_RARM, ({ 20, 20, 20 }), 10, "right arm");
   set_hitloc_unarmed(H_LEGS, ({ 25, 25, 25 }), 20, "legs");
   trig_new("%w 'pats' 'you' %s", "react_pat");
   set_alarm(1.0,0.0,"items");
}
void
items()
{
   object it;
   seteuid(getuid(TO));
   it = clone_object("/d/Kalad/common/wild/pass/obj/bed_feather");
   it -> move(TO);
   MONEY_MAKE_GC(random(25))->move(TO,1);
}
int
react_pat(string who, string dummy) {
   if (who) {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_pat",who);
      return 1;
   }
}
void
return_pat(string who) {
   object obj;
   int ran;
   if (obj = present(who, environment())) {
      command("growl " + (obj->query_real_name()));
      command("kill " + lower_case(obj->query_real_name()));
   }
}
