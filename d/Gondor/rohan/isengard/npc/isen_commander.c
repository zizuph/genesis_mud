/*
 *    /d/Gondor/rohan/isengard/npc/isen_commander
 *
 *    Opus, 1997
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
    set_short("fearless officer");
    set_name("officer");
    add_name( ({"man", "dunlending"}));
    set_pname("officers");
    add_pname( ({"men", "dunlendings"}));
    set_race_name("human");
    set_adj("fearless");
    set_long( BSN(
       "Standing before you is a very highly decorated officer and is one "+
       "of the highest ranked followers of Saruman. He is standing proud, "+ 
       "and looks to be a great warrior."));
    
    set_stats( ({ 90 + random(15),
                  95 + random(15),
                  89 + random(15),
                  70 + random(10),
                  70 + random(10),
                  88 + random(15) }));
    set_alignment( -450 - random(150));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_skill(SS_WEP_SWORD,     80 + random(10));
    set_skill(SS_PARRY,         45 + random(20));
    set_skill(SS_DEFENCE,       85 + random(15));
    set_skill(SS_AWARENESS,     50 + random(15));
    set_skill(SS_BLIND_COMBAT,  70);

    set_chat_time( random(15) + 20);
    add_chat("Look alive everyone! Saruman is watching.");
    add_chat("Keep an eye out, we don't want any uninvited visitors.");
    add_chat("Where is that sniveling little troll Wormtongue at?");
    set_cchat_time(12);
    add_cchat("Drop to your knees cowering dog!");
    add_cchat("Prepare to meet your maker!");
    add_cchat("This will be the last mistake in your puny little life!");
    add_cchat("shout Guards! Intruder!");
    set_cact_time(17);
    add_cact("knee all");
    add_cact("emote eyes turn blood red with anger.");
    add_cact("spit disgust");

    MONEY_MAKE_SC( 40 + random(10))->move(TO);
    MONEY_MAKE_GC( 10 + random(12))->move(TO);
    MONEY_MAKE_PC(  1 + random(2))->move(TO);
    set_equipment( ({WEP_DIR + "dulsword",
                    ISEN_DIR + "arm/brigandine",
                    ISEN_DIR + "arm/whhelm"}));
}

int query_knight_prestige() { return 1250; }


