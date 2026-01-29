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

#define TYPE    ({"young", "dainty", "happy", "nice", \
    "prissy"})
#define PHYS    ({"tanned", "clean", "blond-haired", "blue-eyed", \
    "brown-haired", "freckle-faced", "auburn-haired"})

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
    set_name("girl");
    add_name(npc_name);

    set_short(type + " " + phys + " girl");
    set_long("This is a " + query_short() + ". She is one of the girls who " +
        "live on the farm. Her hair has been braided into two pony-tails. " +
        "They are tied in bright ribbons. She thinks she's pretty and " +
        "adorable, though her brother disagrees. If given a chance, she " +
        "is liable to talk your ear off.\n");

    set_gender(G_FEMALE);
    add_prop(CONT_I_WEIGHT,37000);
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
    add_act("emote skips around around you merrily.");
    add_act("emote brushes her dress clean.");
    add_act("emote puts her hand up to her mouth and stiffles a giggle.");
    add_act("emote smiles happily at you.");
    add_act("emote looks around.");
    add_chat("My mom makes me help her all the time.");
    add_chat("Boys are so gross and dirty.");
    add_chat("Girls rule, and boys drool!");
    add_chat("Boys are icky!");
    add_chat("My pa says I'm his favorite girl.");
    add_chat("Girls are smarter because they play harder. Boys " +
        "are dumb because they suck their thumb!");
    add_chat("Boys are gross. They are dirty and ugly!");
    add_chat("My mom says I'm the prettiest girl ever.");
    add_chat("I'm prettier than you are.");
    add_chat("I'm a little princess!");

    set_cchat_time(5);
    add_cchat("Oh, I can't believe you're beating me up!");
    add_cchat("What are you fighting me for?");
    add_cchat("You are such a bully!");
    add_cchat("Just wait until my parents hear about this, they will kill you!");
    add_cchat("Take that, and that, and that!");
    add_cchat("You are mean!");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    arm_me();

    set_random_move(8);
}

void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    wep = clone_object(FWEP_DIR + "dagger");
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
