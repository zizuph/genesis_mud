#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#define A_RFANG 0
#define A_LFANG 1
#define A_TAIL 2
#define H_HEAD 0
#define H_BODY 1

public void
create_creature()
{
    set_name("snake");
    set_living_name("_garden_snake_");
    set_race_name("snake");
    set_adj(({"green-yellow", "striped", "green", "yellow"}));
    set_short("green-yellow striped snake");
    set_long("A little snake with green and yellow stripes.\n");
    default_config_creature(5);
    set_random_move(60);
    set_restrain_path("/d/Earthsea/gont/tenalders/village/");
    set_monster_home("/d/Earthsea/gont/tenalders/village/witch_garden_7");
    set_m_in("slithers in");
    set_m_out("slithers away");
    set_skill(SS_UNARM_COMBAT, 5);
    set_skill(SS_DEFENCE, 5);
    remove_prop(OBJ_M_NO_GET);
    set_attack_unarmed(A_TAIL, 10, 20, W_BLUDGEON, 30, "little tail");
    set_attack_unarmed(A_RFANG, 10, 20, W_IMPALE, 35, "right fang");
    set_attack_unarmed(A_LFANG, 10, 20, W_IMPALE, 35, "left fang");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(80);
    add_act("emote goes hissssssssssssssssssssssssss.");
    add_act("emote wiggles across your foot.");
    add_prop(OBJ_M_HAS_MONEY, ({ 0, 0, 1, 0}));
}
