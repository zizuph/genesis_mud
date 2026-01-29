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

    type = "dirty";
    phys = "sneaky";

    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name("bandit");
    add_name("bandit_train");
    add_name("trainer");

    set_short(type + " " + phys + " bandit");
    set_long("This is a " + short() + ". He looks swarthy and unkempt, with " +
        "an evil glint in his eye. He looks muscular and ready to rob " +
        "anyone. However, he watches the shop, to make sure the boss " +
        "isn't robbed.\n");

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
    set_chat_time(4);
    add_chat("There are many travellers on the road to steal from.");
    add_chat("Have you got anything we can use?");
    add_chat("Those patrols are so stupid, they don't know where we are.");
    add_chat("We control this stretch of the High Road.");
    add_chat("We have been here for several months now.");
    add_chat("Our hideout is well hidden.");

    add_act("grin wicked");
    add_act("watch");
    add_prop(LIVE_I_NEVERKNOWN, 1);

}

void
init_living()
{
    ::init_living();
}

