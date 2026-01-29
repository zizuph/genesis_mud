/*
 * /d/Gondor/morgul/npc/ithil_orc.c
 *
 * Olorin, July 1993
 * General upgrade, Olorin, February 1996
 *      Modified 11-4-2009 by Eowul, Updated stats
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_ithil_orc()
{
}

nomask void
create_ithil_monster()
{
    int     rnd = random(31);
 
    set_short("black-skinned orc");
    set_pshort("black-skinned orcs");
    set_name("orc");
    set_pname("orcs");
    set_race_name("orc"); 
    set_adj(alignlook());
    set_adj("black-skinned");
    set_long(CAP(LANG_ADDART(implode(query_adjs()," ")))
       +  " orc with short crooked legs and long arms that hang almost "
       +  "to the ground.\n");
    
    default_config_npc( 100 + rnd);
    set_base_stat(SS_INT, 80 + rnd);
    set_base_stat(SS_WIS, 80 + rnd);
    set_base_stat(SS_DIS, 125 + rnd);

    set_alignment(-250-rnd*10);

    set_skill(SS_WEP_SWORD,  55 + rnd / 2);
    set_skill(SS_WEP_CLUB,   55 + rnd / 2);
    set_skill(SS_WEP_KNIFE,  55 + rnd / 2);
    set_skill(SS_PARRY,      55 + rnd / 2);
    set_skill(SS_DEFENCE,    55 + rnd / 2);
    add_prop(CONT_I_HEIGHT,   150 + rnd / 2);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 400);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 400);    
    add_prop(LIVE_I_SEE_DARK, 4);

    set_chat_time(15 + random(15));
    add_chat("Curse you!");
    add_chat("Stop squeaking, you dunghill rat!");
    add_chat("Those nazgul give me the creeps!");
    add_chat("Lugburz wants it, we do it!");

    set_cchat_time(5 + random(10));
    add_cchat("Finish it!");
    add_cchat("Curse you, you little maggot!");
    add_cchat("Come here, and I'll squeeze your eyes out!");

    set_act_time(15 + random(15));	
    add_act("burp");
    add_act("get all from corpse");
    add_act("hiss");
    add_act("grin");		
    add_act("fart");		

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("@@enemy_emote|kick@@"); 
    add_cact("@@enemy_emote|snarl@@"); 
    add_cact("@@enemy_emote|glare@@"); 

    create_ithil_orc();
}

