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
void
create_monster() {
   set_name("guard");
   set_race_name("wyrmman");
   set_adj("reptilian");
   set_adj("large");
   set_gender(2);
   set_alignment(-100);
   set_aggressive(0);
   set_stats(({ 50, 40, 55, 25, 30, 40 }));
   set_hp(500);
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_BLIND_COMBAT, 75);
   set_skill(SS_PARRY, 40);
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
   set_act_time(10);
   add_act("emote takes a frighteningly aggressive posture " +
      "and bares his claws at you.");
   add_act("emote stands perfectly still and glares at you " +
      "intently.");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   clone_object("/d/Rhovanion/common/dungeon1/gear/warmour1.c")
   ->move(TO);
   ob1 = MONEY_MAKE(36, "silver")->move(TO);
   command("wear all");
   return 1;
}
