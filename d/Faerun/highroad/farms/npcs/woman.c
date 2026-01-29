/*
 * Farm Wife
 * by Finwe, August, 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";

void arm_me();
void create_monster()
{
    int i;

    seteuid(getuid());
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    npc_name = "_farm_human";

    add_adj("middle-aged");
    add_adj("distracted");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name(npc_name);
    add_name("woman");
    set_short("middle-aged distracted woman");
    set_long("This is a " + query_short() + ". Her long, blond hair is braided into one long braid. Her happy disposition shines on her face. Her tanned skin shows she works outdoors quite a bit in the garden and probably helps out on the farm. As the woman of the farm, she looks like she takes care of everyone very well.\n");
        
    set_gender(G_FEMALE);
    add_prop(CONT_I_WEIGHT,85000);
    add_prop(CONT_I_HEIGHT,190);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 80 + random(25));
    set_base_stat(5, 80);

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_2H_COMBAT, 50);

   /* Actions */
    set_act_time(5);
    set_cact_time(5);
    add_act("emote scurries around room, cleaning it.");
    add_act("emote chases a child away.");
    add_act("emote brushes pushes a stray hair back over an ear.");
    add_act("emote smiles happily.");
    add_act("emote sighs deeply.");
    add_act("emote scratches her nose.");

    add_chat("This family keeps me busy.");
    add_chat("Things get busy around here at mealtime.");
    add_chat("Please don't make a mess, I'll have to clean it up later.");
    add_chat("Those kids keep me busy all day long.");
    add_chat("Life on a farm is kind of laid back.");
    add_chat("That husband of mine is always busy.");
    
    set_cchat_time(5);
    add_cchat("Die, you scabrous mongrel!");
    add_cchat("What are you fighting me for?");
    add_cchat("You will die for this crime!");
    add_cchat("Just wait until my husband hears about this, he will kill you!");
    add_cchat("Take that, and that, and that!");
    add_cchat("I can't believe you are doing this!");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

    set_pick_up_team(({npc_name}));
}

void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    wep = clone_object(FWEP_DIR + "butcher");
    wep -> move(TO);
    arm = clone_object(FARM_DIR + "dress");
    arm -> move(TO);

    command("wield weapon");
    command("wear all");
}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}
