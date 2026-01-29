/* 
 * /d/Kalad/common/wild/pass/npc/mo_dog.c
 * Purpose    : A mountain ogre dog
 * Located    : /d/kalad/common/wild/pass/desert/rock/
 * Created By : ??.??.?? Antharanos
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
   set_name("dog");
   set_race_name("dog");
   set_adj("wild");
   add_adj("desert");
   set_long("A wild dog native to the desert clime of the Great Kalad "+
      "Waste. Its sandy brown fur, slightly mottled with dark spots, is "+
      "the perfect camouflage for the sandy environment of the waste.\n");
   set_gender(G_NEUTER);
   set_stats(({45,45,45,20,20,55}));
   set_skill(SS_DEFENCE,50);
   set_skill(SS_CLIMB,50);
   add_prop(LIVE_I_NEVERKNOWN, 1);
   add_prop(CONT_I_WEIGHT,45000);
   add_prop(CONT_I_VOLUME,45000);
   add_prop(OBJ_I_NO_INS, 1);
   set_act_time(3);
   add_act("snarl all");
   add_act("growl all");
   add_act("emote makes a long barking sound.");
   set_cact_time(3);
   add_cact("emote emits a short series of barks.");
   set_attack_unarmed(A_BITE, 20, 20, W_IMPALE, 10, "jaws");
   set_attack_unarmed(A_LPAW,   25, 15, W_SLASH, 45, "left paw");
   set_attack_unarmed(A_RPAW,   25, 15, W_SLASH, 45, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 10, 15, 15 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 15, 15, 20 }), 60, "body");
   set_hitloc_unarmed(H_LEGS, ({ 10, 10, 10 }), 20, "legs");
   trig_new("%w 'attacks' %s","react_attack");
}
int
react_attack(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_attack",who);
      return 1;
   }
}
void
return_attack(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("up");
      command("emote jumps up and down excitedly.");
      set_alarm(2.0,0.0,"warning");
   }
}
warning()
{
   command("emote barks out a warning!");
   return;
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("up");
      command("emote barks out a warning!");
   }
}
