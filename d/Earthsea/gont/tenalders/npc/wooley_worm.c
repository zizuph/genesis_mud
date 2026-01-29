#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <money.h>

#define A_FEELER 1
#define A_TAIL 2
#define H_HEAD 0
#define H_BODY 1

public void
create_creature()
{
    set_name("worm");
    set_living_name("_wooley_worm_");
    add_name("caterpillar");
    set_adj(({"fuzzy", "wooley", "brown"}));
    set_short("brown wooley worm");
    set_long("A fuzzy brown wooley worm, which is a kind "+
        "of cute caterpillar.\n");
    default_config_creature(5);
    set_skill(SS_UNARM_COMBAT, 5);
    set_skill(SS_DEFENCE, 5);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NO_BODY, 1);
    add_prop(CONT_I_WEIGHT, 15+random(10));
    add_prop(CONT_I_VOLUME, 5+random(10));
    remove_prop(OBJ_M_NO_GET);
    set_restrain_path("/d/Earthsea/gont/tenalders/village/");
    set_monster_home("/d/Earthsea/gont/tenalders/village/witch_garden_3");
    set_attack_unarmed(A_TAIL, 10, 20, W_BLUDGEON, 30, "little tail");
    set_attack_unarmed(A_FEELER, 10, 20, W_BLUDGEON, 30, "antenna");
    set_attack_unarmed(A_MOUTH, 10, 20, W_IMPALE, 30, "mouth");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(35);
    add_act("emote nibbles on a leaf.");
    add_act("emote climbs a stem.");
    set_random_move(35);
    set_m_in("inches in");
    set_m_out("inches away");
    (MONEY_MAKE_GC(1))->move(this_object(), 1);
}
