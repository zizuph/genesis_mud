#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";

#include <ss_types.h>
#include "defs.h"

#define ADJS ({ "tiny", "nasty", "nasty", "scowling", "pimpled" })
#define COLOURS ({ "pale", "green-skinned", "wrinkled",\
    "scary", "smelly" })

public void
create_earthsea_monster()
{
    string adj1 = ADJS[random(sizeof(ADJS))],
        adj2 = COLOURS[random(sizeof(COLOURS))];
    set_adj(({ adj2, adj1 }));
    set_name("goblin");
    set_short(adj1 + " " + adj2 + " goblin");
    set_pshort(adj1 + " " + adj2 + " goblins");
    add_name("smuggler");
    set_race_name("goblin");
    set_height("very short");
    set_width("fat");
    set_long("This character looks very mean and "+
       "rotten. You suspect that he is some sort of criminal.\n");
    set_stats(({ 20, 15, 15, 2, 2, 60 }));
    add_equipment(({ WEP + "c_dagger", ARM + "gobbo_shorts"}));
    set_skill(SS_WEP_KNIFE, 25);
    set_skill(SS_DEFENCE, 15);
    set_act_time(45);
    add_act("snarl all");
    set_skill(SS_HIDE, 20);
    set_skill(SS_SNEAK, 20);
}
