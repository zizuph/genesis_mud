#pragma save_binary

inherit "/std/monster";
inherit "/d/Gondor/common/ship/pel_tours";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "defs.h"

void
create_monster()
{
    set_name("grosso");
    add_name("captain");
    set_living_name("grosso");
    set_title("the Strong");
    set_race_name("human");
    set_adj("strong");
    add_adj("suntanned");
    set_stats(({ 260, 60, 60, 160, 90, 90 }));
    set_skill(SS_SWIM, 100);
    set_skill(SS_LOC_SENSE,100);
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,50);
    heal_hp(10000);

    add_prop(OBJ_I_NO_ATTACK, 1);
    set_default_answer(QCTNAME(this_object()) + " says: I do not know what you are talking about.\n");
    set_up_pelargir_tour();
}

void
do_introduce(object tp)
{
    if (!present(tp, ENV(TO)))
        return;

    command("introduce me to "+ tp->query_real_name());
}

void
add_introduced(string str)
{
    if (TP->query_npc() || TP->query_met(query_name()))
        return;

    set_alarm(2.0, 0.0, &do_introduce(TP));
}

