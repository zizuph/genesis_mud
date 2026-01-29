
/*
 * citizen_f.c
 * Female citizen
 * Town of Haven
 * Tibbit, 16 Feb 1998
 *
 */

inherit "/d/Krynn/std/monster";
inherit "/std/act/domove";

#include "../local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <money.h>
#include <stdproperties.h> 

//Adjectives.
string *adj_list = ({"hardworking","tired","energetic"});
string *adj_list2 = ({"tall","short","thin","wan","pale","tanned"});

void
create_krynn_monster()
{
    string adj1,adj2;

    adj1 = adj_list[random(sizeof(adj_list))];
    adj2 = adj_list2[random(sizeof(adj_list2))];

    set_race_name("human");
    set_name("citizen");
    set_adj(adj1);
    add_adj(adj2);

    set_gender(1);

    set_short(adj1 + " " + adj2 + " female human");
    set_long("This "+adj1+" "+adj2+" human is one of the "+
        "hardworking citizens of the town of Haven.  They "+
        "follow the teachings of the seekers, and search for signs "+
        "of the new gods.\n");

    set_stats(({
        17 + random(15),
        20 + random(15),
        19 + random(15),
        17 + random(15),
        18 + random(15),
        16 + random(15) }));

    set_skill(SS_DEFENSE, 12);
    set_skill(SS_UNARM_COMBAT, 10);

    set_act_time(14);
    add_act("say The seekers assure us that the new gods are true.");
    add_act("smile thoug");
    add_act("say We are simple farmers, here.");
    add_act("emote looks momentarily to the seeker temple at the "+
        "center of the town of Haven.");
    add_act("say Welcome to Haven, our home.");

    add_ask("[about] 'haven' / 'town'",
        "say This is our home.", 1);
    add_ask("[about] 'seeker' / 'seekers'",
        "say The Seekers are very wise.  They show us the way "+
        "to the new gods.", 1);
    add_ask("[about] 'temple'",
        "say We constructed the temple for the Seekers, "+
        "our spiritual leaders.", 1);

    set_random_move(5,0);
    set_restrain_path(HDIR);

    add_prop(LIVE_I_NEVERKNOWN,1);

    set_alarm(0.5,0.0,"arm_me");

}

void
arm_me()
{
    reset_euid();

    MONEY_MAKE_CC(random(10)+1)->move(TO);

}

