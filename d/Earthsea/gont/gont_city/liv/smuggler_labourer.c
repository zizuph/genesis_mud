#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";

#include <ss_types.h>
#include "defs.h"

#define ADJS ({ "strong", "sweaty", "powerful", "swarthy" })

public void
create_earthsea_monster()
{
    string adj = ADJS[random(sizeof(ADJS))];
    set_adj(({ adj, "goblin"}));
    set_name("worker");
    add_name("smuggler");
    set_short(adj + " goblin worker");
    set_pshort(adj + " goblin workers");
    set_race_name("goblin");
    set_height("short");
    set_width("plump");
    set_long("This goblin labourer looks very mean and " +
        "rotten. You suspect that he may be some sort of " +
        "criminal.\n");
    set_stats(({ 85, 74, 80, 65, 65, 70 }));
    add_equipment(({ WEP + "hammer", ARM + "gobbo_shorts"}));
    set_skill(SS_WEP_CLUB, 55);
    set_skill(SS_DEFENCE, 55);
    set_act_time(85);
    add_act("grumble tired");
    add_act("say Work work work. Lift lift lift. Grrr...");
}
