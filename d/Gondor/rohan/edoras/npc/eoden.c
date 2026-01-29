/*
 *    /d/Gondor/rohan/isengard/npc/eoden
 *
 *    Opus, 1998
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
    set_name("eoden");
    add_name("man");
    set_race_name("human");
    set_adj( ({"tall", "distinguished"}));
    set_long( BSN(
        " A man. "));
       
    set_stats( ({ 60 + random(15),
                  70 + random(15),
                  60 + random(15),
                  65 + random(10),
                  65 + random(10),
                  70 + random(15) }));
    set_alignment( 450 + random(450));
    set_skill(SS_WEP_SWORD,     70 + random(10));
    set_skill(SS_PARRY,         20 + random(20));
    set_skill(SS_DEFENCE,       75 + random(15));
    set_skill(SS_AWARENESS,     50 + random(15));
    set_skill(SS_BLIND_COMBAT,  25);

    set_chat_time(35);
    add_chat("Finally, time to relax and get a cold drink.");
    add_chat("I look foreward to a peacefull night at the inn.");
    add_chat("Better enjoy this while I can, I have a rough day ahead.");
    set_cchat_time(12 + random(3));
    add_cchat("How dare you attack me!\n Do you know who I am?\n");
    add_cchat("Wait until the King hears of your actions!");
    add_cchat("Guards! I need help!");
    
    MONEY_MAKE_SC( 40 + random(10))->move(TO);
    MONEY_MAKE_GC( 10 + random(12))->move(TO);
    MONEY_MAKE_PC(  1 + random(2))->move(TO);
    set_equipment( ({EDORAS_DIR + "obj/robe.c",
                     EDORAS_DIR + "obj/eodenssword.c"}));
}

int query_knight_prestige() { return -5; }


