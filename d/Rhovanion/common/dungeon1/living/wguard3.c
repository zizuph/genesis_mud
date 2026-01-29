inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <money.h>
#define A_LCLAW 0
#define A_RCLAW 1
#define H_HEAD 0
#define H_BODY 1
#define H_LARM 2
#define H_RARM 3
#define H_LLEG 4
#define H_RLEG 5
static int awake;
void
create_monster() {
   set_name("guard");
   set_race_name("wyrmman");
   set_adj("reptilian");
   set_adj("large");
   set_long("@@dependent_awake");
   set_gender(2);
   set_alignment(-100);
   set_aggressive(0);
   set_stats(({ 70, 60, 80, 30, 50, 40 }));
   set_hp(500);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_BLIND_COMBAT, 75);
   set_skill(SS_PARRY, 45);
   add_prop(CONT_I_WEIGHT, 99000);
   add_prop(CONT_I_HEIGHT, 2200);
   add_prop(CONT_I_VOLUME, 85000);
   set_attack_unarmed(A_LCLAW, 35, 30, W_SLASH, 50, "left claw");
   set_attack_unarmed(A_RCLAW, 35, 30, W_SLASH, 50, "right claw");
   set_hitloc_unarmed(H_HEAD, ({ 15, 10, 10, 15 }), 10, "head");
   set_hitloc_unarmed(H_BODY, ({  0,  0,  0,  0 }), 20, "body");
   set_hitloc_unarmed(H_LARM, ({  0,  0,  0,  0 }), 25, "left arm");
   set_hitloc_unarmed(H_RARM, ({  0,  0,  0,  0 }), 25, "right arm");
   set_hitloc_unarmed(H_LLEG, ({  0,  0,  0,  0 }), 10, "left leg");
   set_hitloc_unarmed(H_RLEG, ({  0,  0,  0,  0 }), 10, "right leg");
   trig_new("%w 'says:' %s", "react_say");
   trig_new("%w 'rsays:' %s", "react_say");
   trig_new("%w 'shouts:' %s", "react_say");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   ob1 = MONEY_MAKE(50,"copper")->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/loincloth.c")
   ->move(TO);
   command("wear all");
   return 1;
}
public void
part_woke(string target)
{
   seteuid(getuid(TO));
   awake = 1;
   TP->attack_object(find_player(target));
   command("kill " + target);
}
public string
dependent_awake() {
   if (!awake)
      return "This creature lies sleeping on its tatami map. " +
   "It appears to be some sort of humanoid reptile like " +
   "a dragon man, but bears few dragon exclusive features. " +
   "Horns protrude from its head in various places, its eyes " +
   "are yellow and slitted, and long teeth extend from its " +
   "wyrm-like mouth.  The creature also sports long claws on " +
   "both its hands and feet, and its body is covered not in " +
   "skin, but in a harder, leatherier grey hide.  You'd better " +
   "not wake it\n";
   return "Someone has waken this humanoid creature! " +
   "It appears to be some sort of humanoid reptile like " +
   "a dragon man, but bears few dragon exclusive features. " +
   "Horns protrude from its head in various places, its eyes " +
   "are yellow and slitted, and long teeth extend from its " +
   "wyrm-like mouth.  The creature also sports long claws on " +
   "both its hands and feet, and its body is covered not in " +
   "skin, but in a harder, leatherier grey hide. It looks " +
   "angry\n";
}
int
react_say(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_say",who);
      return 1;
   }
}
void
return_say(string who)
{
   object obj;
   int ran;
   if(obj = present(who,environment()))
      {
      awake = 1;
      command("emote stands up and roars!");
      command("kill " + (obj->query_real_name()));
      command("open chest");
      command("shout Aiyeee, dost nuditity!");
      command("get all from chest");
      command("emote hisses at you.");
      command("wear all");
   }
}
void
attacked_by(object ob) {
   awake=1;
   set_alarm(1.0,0.0,"return_say");
}
