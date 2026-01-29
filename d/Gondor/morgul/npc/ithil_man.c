/* 
 *      /d/Gondor/morgul/npc/ithil_man.c
 *
 *      Olorin, July 1993
 *      Modified 11-4-2009 by Eowul, Updated stats
 */
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_ithil_man()
{
}

nomask void
create_ithil_monster()
{
    int     rnd = random(31);

    set_name("man");
    add_name(({"haradrim", "southron", }));
    set_pname(({"men", "haradrim", "humans", "southrons", }));
    set_pshort("swarthy southrons");
    set_race_name("human"); 
    set_adj("swarthy");
    set_adj(alignlook());
    set_long("A tall swarthy man from Harad or Khand in the "
      + "south, with a face like a skull and burning eyes.\n");
    
    default_config_npc( 100 + rnd);
    set_base_stat(SS_INT, 90 + rnd);
    set_base_stat(SS_WIS, 95 + rnd);
    set_base_stat(SS_DIS,110 + rnd);
    set_alignment( -250 - rnd * 10);

    set_skill(SS_WEP_SWORD,   55 + rnd);
    set_skill(SS_WEP_POLEARM, 55 + rnd);
    set_skill(SS_WEP_CLUB,    55 + rnd);
    set_skill(SS_WEP_AXE,     55 + rnd);
    set_skill(SS_WEP_KNIFE,   55 + rnd);

    set_skill(SS_PARRY,    55 + rnd);
    set_skill(SS_DEFENCE,  55 + rnd);

    add_prop(CONT_I_HEIGHT,   170 + rnd);
    add_prop(CONT_I_WEIGHT, 75000 + rnd * 500);
    add_prop(CONT_I_VOLUME, 70000 + rnd * 500);    
    add_prop(LIVE_I_SEE_DARK,   2);

    set_chat_time(25+random(15));
    add_chat("Curse you!");
    add_chat("Stop squeaking, you dunghill rat!");
    add_chat("Those nazgul give me the creeps!");
    add_chat("I hate these stinking orcs!");

    set_cchat_time(5+random(10));
    add_cchat("Finish it!");
    add_cchat("Curse you, you little maggot!");
    add_cchat("Come here, and I'll squeeze your eyes out!");

    set_act_time(15 + random(15));	
    add_act("burp");
    add_act("get all from corpse");
    add_act("hiss");
    add_act("grin");		

    set_cact_time(2 + random(2));
    add_cact("scream"); 
    add_cact("@@emote_enemy|kick@@");
    add_cact("@@emote_enemy|spit@@");
    add_cact("@@emote_enemy|snarl@@");

    create_ithil_man();
}

