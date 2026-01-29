/*
 *    /d/Gondor/rohan/isengard/npc/isen_captain
 *
 *    Opus, Aug 1997
 *
 */
#pragma strict_types

#include "/d/Gondor/defs.h"

inherit ISEN_DIR + "npc/isengard_monster";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
create_isengard_monster()
{
    set_name("captain");
    add_name( ({"man", "dunlending", "officer"}));
    set_pname("captains");
    add_pname( ({"men", "dunlendings", "officers"}));
    set_short("brave captain");
    set_race_name("human");
    set_adj("brave");
    set_long( BSN(
        "Standing before you is one of the officers in charge of Isengard's "+
        "army. He appears to be a born warrior and glares at all around "+
        "him with contempt."));
    set_alignment(-400 - random(175));
    set_stats( ({ 90 + random(10),
                  95 + random(10),
                  88 + random(10),
                  70 + random(5),
                  70 + random(5),
                  88 + random(10)}));
    set_skill(SS_WEP_SWORD,     random(10) + 75);
    set_skill(SS_PARRY,         random(30) + 20);
    set_skill(SS_DEFENCE,       random(15) + 75);
    set_skill(SS_AWARENESS,     random(20) + 35);
    set_skill(SS_BLIND_COMBAT,   60);

    set_chat_time( random(15) + 20);
    add_chat("What are you doing here?");
    add_chat("I want the head of a Ranger as a trophy.");
    add_chat("Our time of glory will soon be at hand.");
    set_cchat_time(14);
    add_cchat("Time to die, worm!");
    add_cchat("shout Intruders! Get reinforcements!");
    add_cchat("Give it up while you still have a chance!");
    
    MONEY_MAKE_SC( 35 + random(10))->move(TO); 
    MONEY_MAKE_GC( 12 + random(10))->move(TO);
    set_equipment( ({WEP_DIR + "dulsword",
                    ISEN_DIR + "arm/brigandine",  
                    ISEN_DIR + "arm/whhelm"}));
}
