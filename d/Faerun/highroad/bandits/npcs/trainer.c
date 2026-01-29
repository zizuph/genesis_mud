/*
 * Bandit for that area
 * by Finwe, July, 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/lib/unique";


nomask void create_faerun_npc()
{
    string type, phys;
    int i;

    seteuid(getuid());

    type = "swarthy";
    phys = "muscular";

    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name("bandit");
    add_name("bandit_train");
    add_name("trainer");

    set_short(type + " " + phys + " bandit");
    set_long("This is the bandit's trainer. He looks strong and unkempt. " +
        "His body is sinewy and lean. From the looks of him, he could " +
        "probably teach you basic skills to become a better bandit.\n");

    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_HEIGHT,200);
    add_prop(LIVE_I_SEE_DARK,10);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 120 + random(25));
    set_base_stat(5, 100);

    set_alignment(-110 + random(-50));

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,90);
    set_skill(SS_WEP_CLUB,90);
    set_skill(SS_WEP_SWORD,90);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

    add_prop(OBJ_M_NO_ATTACK,"You lack the skills to attack him.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK,1);

   /* Actions */
    set_act_time(5);
    
    add_act("' There are many travellers on the road to steal from.");
    add_act("' Those patrols are so stupid, they don't know where we are.");
    add_act("' We control this stretch of the High Road.");
    add_act("' Our hideout is well hidden.");
    add_act("' I can teach you many skills.");
    add_act("' Whatcha looking at? Have ya come to learn or to look stupid?");
    add_act("' If ya got the coins, I can teach ya.");
    add_act("' There's much to learn about being a bandit.");
    add_act("' Get over here so I can teach ya.");
    add_act("grin wicked");
    add_act("watch");
    add_act("emote watches you carefully.");
    add_act("flex");
    add_prop(LIVE_I_NEVERKNOWN, 1);

}

void
init_living()
{
    ::init_living();
}

