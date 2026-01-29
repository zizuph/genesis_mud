/* 
 *  Random farmer kid
 *
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
inherit "/lib/unique";

#define TYPE    ({"young", "carefree", "obnoxious", "mischevious", \
    "wild"})
#define PHYS    ({"tanned", "dirty", "blond-haired", "blue-eyed", \
    "brown-haired", "smelly", "lanky"})

void arm_me();

void create_monster()
{
    string type, phys;
    int i;

    seteuid(getuid());
    if (!IS_CLONE) 
        return;

    type = ONE_OF_LIST(TYPE);
    phys = ONE_OF_LIST(PHYS);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    npc_name = "_farm_human";

    add_adj(type);
    add_adj(phys);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    set_name("boy");
    add_name(npc_name);

    set_short(type + " " + phys + " boy");
    set_long("This is a " + query_short() + ". He is one of the kids that " +
        "lives on the farm. He looks like he works hard and tries to " +
        "get into trouble.\n");

    set_gender(G_MALE);
    add_prop(CONT_I_WEIGHT,40000);
    add_prop(CONT_I_HEIGHT,160);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 10 + random(20));
    set_base_stat(5, 20);

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_WEP_AXE,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_2H_COMBAT, 50);

   /* Actions */
    set_act_time(15);
    set_cact_time(15);
    add_act("emote crosses his eyes at you, then laughs crazily.");
    add_act("emote sticks his tongue out at you.");
    add_act("emote looks around for something to get into.");
    add_act("emote smiles happily at you.");
    add_act("emote wrinkles his nose, then rubs the back of his hand acrossed it.");
    add_chat("Milking those cows is alot of hard work.");
    add_chat("I hate chickens. They are so noisy!");
    add_chat("Boys rule, and girls drool!");
    add_chat("Girls have cooties!");
    add_chat("Oh, I hate when pa makes me clean out the barn.");
    add_chat("Boys are smarter because they play harder. Girls " +
        "are dumb because they suck their thumb!");
    add_chat("Snakes are such cool animals. I love them!");
    add_chat("I love catching polliwogs. They are lots of fun!");
    add_chat("I put a snake in my sister's bed last night. That was so funny!");
    add_chat("Let's go make mudpies!");
    add_chat("I can run faster than you!");
    add_chat("My dad can beat up your dad!");

    set_cchat_time(5);
    add_cchat("You're a bully!");
    add_cchat("What are you fighting me for?");
    add_cchat("My pa will have your hide when hears about this!");
    add_cchat("Just wait until my parents hear about this, they will kill you!");
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

    wep = clone_object(FWEP_DIR + "dagger");
    wep -> move(TO);
    arm = clone_object(FARM_DIR + "pants");
    arm -> move(TO);
    arm = clone_object(FARM_DIR + "ltunic");
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
