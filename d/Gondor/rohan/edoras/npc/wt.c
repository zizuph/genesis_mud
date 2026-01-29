/*
 *    /d/Gondor/rohan/isengard/npc/wormtongue
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
#include <const.h>

public void
create_isengard_monster()
{
    set_name( ({"grima", "wormtongue", "man"}));
    set_title("Woemtongue, advisor to King Theoden");
    set_race_name("human");
    set_gender(G_MALE);
    add_adj( ({"deformed", "pale"}));
    set_long( BSN(
        " a man."));
       
    set_stats( ({ 60 + random(15),
                  70 + random(15),
                  65 + random(15),
                  65 + random(10),
                  65 + random(10),
                  60 + random(15) }));
    set_alignment( 150 + random(250));
    set_skill(SS_WEP_SWORD,     50 + random(10));
    set_skill(SS_PARRY,         10 + random(20));
    set_skill(SS_DEFENCE,       60 + random(15));
    set_skill(SS_AWARENESS,     45 + random(15));
    set_skill(SS_BLIND_COMBAT,  10);
    /*
    * set_chat_time();
    * add_chat("");
    * add_chat("");
    *  add_chat("");
    *  set_cchat_time();
    *  add_cchat("");
    *  add_cchat("");
    *  add_cchat("");
    */

    MONEY_MAKE_SC( 20 + random(10))->move(TO);
    MONEY_MAKE_GC(  5 + random(5))->move(TO);
    //set_equipment( ({EDORAS_DIR + "",
    //                 EDORAS_DIR + ""}));
}

int query_knight_prestige() { return -1; }


