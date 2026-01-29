inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <money.h>
#include <language.h>
#define A_LCLAW 0
#define A_RCLAW 1
#define H_HEAD 0
#define H_BODY 1
#define H_LARM 2
#define H_RARM 3
#define H_LLEG 4
#define H_RLEG 5
void
create_monster() {
   set_name("krutaan");
   set_race_name("wyrmman");
   set_adj("brawny");
   set_adj("pissed");
   set_title("I'sch maschter of braallers!");
   set_long("This giant of a wyrmman towers over eight " +
      "feet tall and is rippling with muscles.  Right now " +
      "he happens to be pretty wasted.\n");
   set_gender(0);
   set_alignment(-200);
   set_aggressive(0);
   set_hp(50);
   set_stats(({ 50, 30, 50, 15, 25, 50 }));
   set_skill(SS_DEFENCE, 30);
   set_skill(SS_BLIND_COMBAT, 75);
   set_attack_unarmed(A_LCLAW, 35, 30, W_SLASH, 50, "left claw");
   set_attack_unarmed(A_RCLAW, 35, 30, W_SLASH, 50, "right claw");
   set_hitloc_unarmed(H_HEAD, ({ 15, 10, 10, 15 }), 10, "head");
   set_hitloc_unarmed(H_BODY, ({  0,  0,  0,  0 }), 20, "body");
   set_hitloc_unarmed(H_LARM, ({  0,  0,  0,  0 }), 25, "left arm");
   set_hitloc_unarmed(H_RARM, ({  0,  0,  0,  0 }), 25, "right arm");
   set_hitloc_unarmed(H_LLEG, ({  0,  0,  0,  0 }), 10, "left leg");
   set_hitloc_unarmed(H_RLEG, ({  0,  0,  0,  0 }), 10, "right leg");
   set_act_time(3);
   add_act("emote belches and a blasting wave of sound " +
      "sweeps out across the room!");
   add_act("emote belches and an over-powering wave of " +
      "noxious vapors sweep over the room!");
   add_act("emote rips the face off the wyrmman standing " +
      "next to him and belches");
   add_act("say Ka arfo nnnnhu....");
   add_act(({"buy grog","buy grog","buy grog","buy grog",
            "drink all"}));
   add_act("buy grog");
   add_act("drink all");
   add_act("shout Chang! Chang! Chang! Chang!  and slams " +
      "his grog down upon his neighbor's head.");
   trig_new("%s 'introduces' 'himself' %s", "intro_me");
   trig_new("%s 'attacks' %s", "pub_fight");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   ob1 = MONEY_MAKE(36,"silver")->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wpants3.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/whelmet.c")
   ->move(TO);
   command("wear all");
   return 1;
}
intro_me() {
   set_alarm(0.0,0.0,"intro_me2");
   return 1;
}
intro_me2() {
   command("introduce myself");
   return 1;
}
pub_fight() {
   command("emote opens his eyes a bit wider...");
   command("say Isch u fites isch is!");
   set_aggressive(1);
   return 1;
}
