/* 2017-11-06 Malus: Modified in/out messages */ 
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <money.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define A_RPAW 0
#define A_LPAW 1
#define A_TOOTH 2
#define H_HEAD 0
#define H_BODY 1

public void
create_creature()
{
    set_name("gopher");
    set_living_name("_gopher_");
    set_short("brown gopher");
    set_long("A brown gopher who lives in tunnels underground. "+
        "It is furry and cute.\n");
    default_config_creature(5);
    set_random_move(45);
    set_restrain_path("/d/Earthsea/gont/tenalders/village/");
    set_monster_home("/d/Earthsea/gont/tenalders/village/witch_garden_5");
    set_m_in("scurries in");
    set_m_out("scurries off");
    set_mm_in("pops up from a hole in the ground");
    set_mm_out("dives into a tunnel heading");
    set_skill(SS_UNARM_COMBAT, 5);
    set_skill(SS_DEFENCE, 5);
    set_attack_unarmed(A_TOOTH, 10, 20, W_IMPALE, 30, "tooth");
    set_attack_unarmed(A_RPAW, 10, 20, W_BLUDGEON, 35, "right paw");
    set_attack_unarmed(A_LPAW, 10, 20, W_BLUDGEON, 35, "left paw");
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_act_time(80);
    add_act("emote sits on its hind paws and sniffs the air.");
    add_prop(OBJ_M_HAS_MONEY, ({ 0, 0, 1, 0 }));
}
