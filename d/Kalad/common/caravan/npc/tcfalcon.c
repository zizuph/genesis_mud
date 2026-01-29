#include "default.h"
inherit "/d/Kalad/std/monster";

#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1

void
create_kalad_monster()
{
    set_name("falcon");
    set_race_name("falcon");
    set_adj("hunting");
    set_long("A magnificent specimen of a bird of prey. This beautiful "+
      "animal makes you feel insignificant in comparison.\n");
    set_gender(G_NEUTER);
    set_stats(({50, 75, 50, 25, 25, 50}));
    set_skill(SS_DEFENCE, 50);
    set_act_time(6);
    add_act("emote screeches defiantly.");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_M_NO_INS, 1);
    set_attack_unarmed(A_BITE, 30, 30, W_IMPALE, 40, "beak");
    set_attack_unarmed(A_LCLAW, 35, 35, W_SLASH, 30, "left claw");
    set_attack_unarmed(A_RCLAW, 35, 35, W_SLASH, 30, "right claw");
    set_hitloc_unarmed(H_HEAD, ({ 15, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 15 }), 80, "body");
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("emote screeches angrily at you!");
	command("kill " + OB_NAME(ob));
    }
}
