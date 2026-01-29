#include "default.h"
inherit "/d/Kalad/std/monster";

#define A_BITE 0
#define A_LHOOF 1
#define A_RHOOF 2
#define H_HEAD 0
#define H_BODY 1

void
create_kalad_monster()
{
    set_name("camel");
    set_race_name("camel");
    set_adj("two-humped");
    set_long("A camel with two humps, it is probably more used to the Great "+
      "Kalad Waste, a large desert where many camels reside, instead of this "+
      "crowded city. As a result it looks particularly cranky.\n");
    set_stats(({50, 60, 75, 25, 25, 50}));
    set_skill(SS_DEFENCE, 30);
    set_gender(G_NEUTER);

    set_act_time(6);
    add_act("spit all");
    add_act("eat all");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 75000);
    add_prop(OBJ_I_VOLUME, 75000);
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    set_attack_unarmed(A_BITE, 20, 20, W_BLUDGEON, 40, "teeth");
    set_attack_unarmed(A_LHOOF, 30, 20, W_BLUDGEON, 30, "left hoof");
    set_attack_unarmed(A_RHOOF, 30, 20, W_BLUDGEON, 30, "right hoof");
    set_hitloc_unarmed(H_HEAD, ({ 20, 15, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 20 }), 80, "body");
}
