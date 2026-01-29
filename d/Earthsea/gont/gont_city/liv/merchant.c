/* 
 * Merchant for Gont Port, Amelia, 5/3/98
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/remember";
inherit "/d/Earthsea/lib/width_height";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include "defs.h"

public void
create_earthsea_monster()
{
    set_name("klaxos");
    add_name("merchant");
    set_adj("silver-bearded");
    add_adj("corpulent");
    set_race_name("human");
    set_height("tall");
    set_width("fat");
    set_stats(({ 100 + random(25), 100 + random(30),
        110 + random(30), 70, 60, 95 }));
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 90);
    set_skill(SS_WEP_KNIFE, 90);
    set_title("the Andradean merchant");
    set_gender(G_MALE);
    set_random_move(50);
    set_restrain_path(STREET);
    set_chat_time(120);
    set_act_time(120);
    add_chat("I had to work hard to get where I am today.");
    add_act("peer suspiciously");
    add_chat("It's so hard to make a profit these days, "+
        "with all these pirates about!");
    add_act("emote strokes his magnificent silver beard.");
    (MONEY_MAKE_GC(random(10)))->move(this_object());
    add_equipment(({ ARM + "cloak", WEP + "m_dagger", ARM + "ring" }));
}

public void
intro_hook(string str)
{
    object tp = present(str, environment(this_object()));

    if(objectp(tp) && !tp->query_npc() && !tp->query_met("klaxos"))
        command("introduce myself to " + tp->query_real_name());
}
