#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";

#include "basic_sailor.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

public void
create_sailor()
{
    string adj1 = DESC1[random(sizeof(DESC1))];
    ::create_earthsea_monster();
    set_random_move(80);
    set_restrain_path(STREET);
    set_race_name("human");
    set_height("tall");
    set_width("normal");
    set_short(adj1 + " sailor");
    set_name("sailor");
    set_pname("sailors");
    set_gender(G_MALE);
    set_adj(adj1);
    set_act_time(50);
    add_act("grin");
    add_act("flex");
    set_m_in("swaggers in");
    set_m_out("swaggers away");
    add_prop(LIVE_I_NEVERKNOWN, 1);
}

public void
set_levels(int level)
{
    int i = 6;

    while (i--)
    {
        set_base_stat(i, levels[level] + random(10));
    }

    set_hp(query_max_hp());
    set_all_hitloc_unarmed(1);

    set_skill(SS_DEFENCE, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_WEP_AXE, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_PARRY, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_BLIND_COMBAT, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_WEP_SWORD, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_WEP_POLEARM, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_AWARENESS, 45);
    set_skill(SS_WEP_KNIFE, (levels[level] / 3 * 2 ) + random(15));
}
