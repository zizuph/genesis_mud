#include "default.h"
inherit "/d/Kalad/std/monster";

#define A_BITE 0
#define A_LHOOF 1
#define A_RHOOF 2
#define A_HORNS 3
#define H_HEAD 0
#define H_BODY 1

void
create_kalad_monster()
{
    set_name("ox");
    set_race_name("ox");
    set_adj("massive");
    add_adj("grey");
    set_pshort("massive grey oxen");
    set_long("A large grey ox, although slow-moving and stupid, it looks "+
      "quite powerful.\n");

    set_stats(({100, 50, 100, 25, 25, 75}));
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 30);
    set_gender(G_NEUTER);

    set_act_time(6);
    add_act("eat all");
    add_act("emote grunts.");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 150000);
    add_prop(OBJ_I_VOLUME, 150000);
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);

    set_attack_unarmed(A_BITE, 25, 25, W_BLUDGEON, 20, "jaws");
    set_attack_unarmed(A_LHOOF, 35, 35, W_BLUDGEON, 30, "left hoof");
    set_attack_unarmed(A_RHOOF, 35, 35, W_BLUDGEON, 30, "right hoof");
    set_attack_unarmed(A_HORNS, 30, 30, W_IMPALE, 20, "horns");
    set_hitloc_unarmed(H_HEAD, ({ 20, 20, 25 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 15, 15, 30 }), 80, "body");
}
