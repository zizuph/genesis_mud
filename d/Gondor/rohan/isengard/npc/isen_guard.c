/*
 *    /d/Gondor/rohan/isengard/npc/isen_guard
 *
 *    Opus, August 1997
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

// Prototypes
string alignlooks();

public void
create_isengard_monster()
{
    set_name("guard");
    add_name( ({"man", "dunlending"}));
    set_pname("guards");
    add_pname( ({"men", "dunlendings"}));
    set_race_name("human");
    set_adj(alignlooks());
    set_long( BSN(
       "Standing before you is a common guard for Isengard. He looks "+
       "tough and ready for anything."));
    set_alignment( -250 - random(200));
    set_stats( ({ 68 + random(10),
                  70 + random(10),
                  70 + random(7),
                  50 + random(10),
                  55 + random(10),
                  70 + random(15)}));
    
    set_skill(SS_WEP_SWORD,     random(15) + 65);
    set_skill(SS_PARRY,         random(25) + 30);
    set_skill(SS_DEFENCE,       random(20) + 60);
    set_skill(SS_AWARENESS,     random(25) + 25);
    set_skill(SS_BLIND_COMBAT,  50);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_chat_time( random(25) + 70);
    add_chat("I need a drink.");
    add_chat("The time for battle draws near.");
    add_chat("I hope our patrol gathers useful information for us.");
    set_cchat_time(18);
    add_cchat("Fall upon my sword you bastard!");
    add_cchat("Die like the worm you are!");

    MONEY_MAKE_SC( 20 + random(20))->move(TO);
    MONEY_MAKE_GC(5)->move(TO);
    set_equipment( ({WEP_DIR + "dubsword",
                    ISEN_DIR + "arm/brigandine",
                    ISEN_DIR + "arm/whhelm"}));
}
string
alignlooks()
{
    string *alignlooks =
       ({"wicked", "corrupt", "mean", "malevolent", "vicious", "foul",
         "menacing", "deadly", "savage", "evil", "cruel", "brutal",
         "ferocious", "unmerciful", "heartless"});
    return alignlooks[random(sizeof(alignlooks))];
}

int query_knight_prestige() { return 800; }

