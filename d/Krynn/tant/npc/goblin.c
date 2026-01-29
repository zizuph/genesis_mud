/*
 * Goblin by Teth Jan 18 97
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include "../local.h"
inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

void
create_krynn_monster()
{

    set_name("goblin");
    set_race_name("goblin");
    set_short("red-skinned goblin");
    set_adj("red-skinned");
    set_pname("goblins");
    set_pshort("red-skinned goblins");
    set_long("This is a red-skinned goblin, as is typical of Krynn. A " +
        "quick appraising glance of the goblin reveals that he is of a " +
        "weaker race than the typical goblin, perhaps due to a lack of " +
        "resources while growing. However, he still looks fairly " +
        "powerful.\n");
    set_adj("menacing");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_alarm(1.0,0.0,"arm_me");
    set_m_in("races in");
    set_m_out("races");

    set_stats(({10,10,10,5,5,10}));
    set_skill(SS_DEFENCE,        10);
    set_skill(SS_WEP_KNIFE,      20);

    set_alignment(-50);
    set_knight_prestige(2);

    set_random_move(50);
    set_restrain_path(TROOM);
    set_monster_home(TROOM + "sewer10");
   
    set_act_time(4);
    add_act("emote snarls viciously.");
    add_act("emote drools endlessly, while staring at you.");
    add_act("emote jumps up and down in a wild display of immaturity.");
    add_act("emote reminds you that you are scum.");
}

public void
arm_me()
{
    clone_object(TWEP + "goblin_knife")->move(TO);
    command("wield all");
}

