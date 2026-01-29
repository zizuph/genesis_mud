/*
 * General NPCs of Faerie
 * By Finwe, March 2005
 */

inherit "/std/monster";
//inherit "/d/Genesis/lib/intro";

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

public string get_race();

void
create_monster()
{
    get_race();
    set_adj("greedy");
    set_adj("friendly");
    set_short("friendly greedy gnome");
    set_long("This gnome is the money-lender of the bank. He's short " +
        "and very preoccupied with his ledgers, and counting and re-"+
        "counting his money. He is greedy and hoards all the money he " +
        "gets behind the counter.\n");

    set_gender(G_MALE);
    set_stats(({ 40,40,40,40,40,40}));

    set_skill(SS_DEFENCE,       100);
    set_skill(SS_UNARM_COMBAT,  100);
    set_skill(SS_AWARENESS,     100);
    set_skill(SS_PARRY,         100);

    set_chat_time(30+random(60));
    add_chat("I CaN kEEP yOUR mOnEy FOR yOu.");
    add_chat("wHAT cAn I hElP yOU WiTh?");
    add_chat("MoNeY iS THe BeSt ThInG iN THe WoRLD!");
    add_chat("I caN OPen An aCCouNT If yOu Do NoT HAve OnE YEt.");
    add_chat("We HAvE ThE BeST RaTEs aNYwHEre.");

    set_act_time(60+random(60));
    add_act("emote counts some money behind the counter.");
    add_act("emote stacks some money behind the counter.");
    add_act("emote writes something down in a ledger.");
    add_act("emote looks up from his ledgers and looks at you.");
    add_act("emote arranges his ledgers carefully.");
    add_act("emote scribbles something down hurriedly");
    add_act("emote polishes a coin.");

}

public string get_race()
{
    string *race, race_name;

// mental appearance
    race = ({"human", "elf", "gnome", "dwarf"});

    race_name = race[random(sizeof(race))];
    set_race_name(race_name);
}

