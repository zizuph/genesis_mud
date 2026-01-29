#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>

#define A_ARM 0
#define A_FOOT 1
#define A_STICK 2
#define H_HEAD 0
#define H_BODY 1

public void
create_earthsea_monster()
{
    set_name("scarecrow");
    set_race_name("scarecrow");
    set_short("raggedy scarecrow");
    set_adj("raggedy");
    set_long("A raggedy scarecrow. He is nothing "+
        "more than a raggedy shirt and pants stuffed "+
        "with straw, and a pumpkin with a face drawn on "+
        "it for a head. He is supported by a stick in the "+
        "ground.\n");
    set_stats(({15, 15, 15, 1,1, 30 }));
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_skill(SS_DEFENCE, 10 + random(10));
    set_skill(SS_UNARM_COMBAT, 10 + random(10));
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NO_BODY, 1);
    set_attack_unarmed(A_ARM, 10, 20, W_BLUDGEON, 33, "empty arm");
    set_attack_unarmed(A_HEAD, 10, 20, W_BLUDGEON, 33, "pumpkin head");
    set_attack_unarmed(A_STICK, 10, 20, W_BLUDGEON, 33, "stick");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(60);
    add_act("shout BOOGEDY BOOGEDY BOO!!");
    add_act("emote tries to frighten you away by flapping his arms.");
    add_act("think if I only had a brain...");
    add_act("emote tries to kick you and falls to the ground.");
    add_act("stare");
    add_equipment(({ "/d/Earthsea/gont/tenalders/arm/scarecrow_shirt",
        "/d/Earthsea/gont/tenalders/arm/scarecrow_pants",
        "/d/Earthsea/gont/tenalders/wep/scarecrow_stick",
        "/d/Earthsea/gont/tenalders/obj/items/straw",
        "/d/Earthsea/gont/tenalders/obj/items/pumpkin" }));
    (MONEY_MAKE_GC(1))->move(this_object(), 1);
}
