#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Krynn/open/auto_teaming";

#include "basic_sailor.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

public void create_dockworker() { }

public nomask void
create_earthsea_monster()
{
    string adj1 = DESC1[random(sizeof(DESC1))];
    set_race_name("human");
    set_height("tall");
    set_width("normal");
    set_name("worker");
    add_name("dockworker");
    set_short(adj1 + " " + "harbour worker");
    set_pshort(adj1 + " " + "harbour workers");
    add_adj("harbour");
    set_gender(G_MALE);
    set_adj(adj1);
    set_act_time(50);
    add_act("flex");
    add_act("emote hauls a load of crates onto the stack.");
    add_chat("Out of my way, big load coming through.");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_pick_up_team("dockworker");
    create_dockworker();
}

public void
set_levels(int level)
{
    default_config_npc(levels[level] + random(10));

    set_skill(SS_DEFENCE, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_WEP_AXE, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_PARRY, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_BLIND_COMBAT, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_WEP_SWORD, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_WEP_POLEARM, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_AWARENESS, 45);
    set_skill(SS_WEP_KNIFE, (levels[level] / 3 * 2 ) + random(15));
    set_skill(SS_UNARM_COMBAT, (levels[level] / 3 * 2) + random(15));
}

public void
init_living()
{
    ::init_living();
    init_team_pickup();
}

public void
attacked_by(object player)
{
    object *team = query_team_others();
    int i;

    ::attacked_by(player);

    if(sizeof(team))
    {
        if(random(2))
        {
            team[0]->command("say Stop that!");
            command("growl .");
        } else {
            team[0]->command("say Hey, we're working here!");
            command("grumble");
        }

        for(i = 0; i < sizeof(team); i++)
        {
            team[i]->command("kill " +
                lower_case(player->query_real_name()));
        }
    }
}
