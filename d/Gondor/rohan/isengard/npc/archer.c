/*
 *    /d/Gondor/rohan/isengard/npc/archer.c
 *
 *    Original by Xeros, 27 Dec 1993
 *
 *    This version:
 *        copyright (c) Robert Miller, 1997
 *
 *    Update:
 *       Adjusted some stats/skills for use in Isengard.
 */

#pragma strict_types

#include "/d/Gondor/defs.h"   

inherit ISEN_DIR + "npc/isengard_monster";

#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

void 
create_isengard_monster() 
{
    set_name("archer");
    set_race_name("human");
    set_pshort("dunlending archers");
    add_name(({"dunlending","man"}));
    set_adj("long-armed");
    add_adj("dark-haired");
    set_long(BSN("A dunlending archer, apparently in the service of Saruman."));
    default_config_npc(85+random(16));
    set_base_stat(SS_DEX,90+random(36));
    set_base_stat(SS_DIS,90+random(16));
    set_base_stat(SS_CON,80+random(21));
    set_base_stat(SS_INT,95+random(16));
    set_alignment(-250-random(101));
    
    set_skill(SS_WEP_SWORD,60+random(16));
    set_skill(SS_WEP_MISSILE,80+random(21));
    set_skill(SS_UNARM_COMBAT,30+random(36));
    set_skill(SS_DEFENCE,50+random(16));
    set_skill(SS_PARRY,40+random(26));
    set_skill(SS_AWARENESS,50+random(21));
    
    add_prop(LIVE_I_NEVERKNOWN,1);
    
    set_chat_time(5+random(6));
    add_chat("Do it, and I'll put an arrow through you faster than you can blink.");
    add_chat("Wonder if Sharkey will let us use Gwath for target practice...");
    add_chat("Just what do you think you are doing here? Out!");
    set_cchat_time(6+random(6));
    add_cchat("I could sure use some reinforcements about now.");
    add_cchat("Just what do you think you are doing here?");
    set_act_time(2+random(8));
    add_act("emote peers alertly about the room.");
    add_act("get all");
    add_act("cackle mad");
    add_act("burp");
    add_act("scratch");
    set_cact_time(4+random(4));
    add_cact("knee all");
    add_cact("kick all");
    add_cact("poke all eye");
    add_cact("tackle all");
    add_cact("shout We are under attack, get in here now!!");

    MONEY_MAKE_SC( 29 + random(35))->move(TO);
    MONEY_MAKE_GC( 5 + random(10))->move(TO);
    set_equipment( ({ISEN_DIR + "wep/dunssword",
                     ISEN_DIR + "arm/brigandine"}));
}

int query_knight_prestige() { return 625; }

