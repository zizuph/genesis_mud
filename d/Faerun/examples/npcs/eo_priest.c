/*
 * /d/Ravenloft/core/darkon/martira_bay/npc/eo_priest.c
 *
 * Eternal Order priest.
 * Coded by Mirandus with significant help from Leia and Nerull.
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <options.h>
#include <money.h>

inherit STD +"mobs/std_mob.c";

void arm_me();

/*
 * Function name: create_monster()
 * Description  : Constructor. Creates the monster.
 */
void create_rav_monster()
{
    seteuid(getuid());

    set_race_name("priest");
    set_name("human");

    set_adj("ash-grey");
    add_adj("hooded");

    set_gender(G_MALE);

	set_short("ash-grey hooded " + query_race_name());

    set_long("The art of fasting has left these priests "
    +"with extremely taunt skin and deeply sunken black eyes. With "
    +"skin so thin you can see the white of bone beneath hands and "
    +"wrists of these macabre living-dead humans, you wonder how "
    +"these priest still draw breath.\n");

    add_prop(CONT_I_WEIGHT, 110000);
    add_prop(CONT_I_HEIGHT, 180);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_stats(({ STAT1_GUARD, STAT2_GUARD, STAT3_GUARD,
        STAT4_GUARD, STAT5_GUARD, STAT6_GUARD }));

    set_hitloc_unarmed(A_HEAD, MARMONSTER_AC, 15, "head");
    set_hitloc_unarmed(A_R_ARM, MARMONSTER_AC, 10, "right arm");
    set_hitloc_unarmed(A_L_ARM, MARMONSTER_AC, 10, "left arm");
    set_hitloc_unarmed(A_BODY, MARMONSTER_AC, 45, "body");
    set_hitloc_unarmed(A_LEGS, MARMONSTER_AC, 20, "legs");


    /*               hit/pen           %% on usage per c-round */
    set_attack_unarmed(W_LEFT, MARMONSTER_HIT, MARMONSTER_PEN, W_BLUDGEON,
        MARMONSTER_USAGE, "left fist");

    set_attack_unarmed(W_RIGHT, MARMONSTER_HIT, MARMONSTER_PEN, W_BLUDGEON,
        MARMONSTER_USAGE, "right fist");

    set_attack_unarmed(W_BOTH, MARMONSTER_HIT, MARMONSTER_PEN, W_BLUDGEON,
        0, "both fists");

    set_attack_unarmed(W_FOOTR, MARMONSTER_HIT, MARMONSTER_PEN, W_BLUDGEON,
        0, "right foot");

    set_attack_unarmed(W_FOOTL, MARMONSTER_HIT, MARMONSTER_PEN, W_BLUDGEON,
        0, "left foot");

    set_skill(SS_WEP_POLEARM, 70);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_UNARM_COMBAT,100);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 1);

    set_act_time(10);

	set_default_answer("The ash-robed hooded priest ignores you.\n");


    add_act("emote yells: We claim the dead, lest the Dead claim Us!");
    add_act("emote yells: Back with you, cursed abonination! The "
    +short()+" raises his bony arms and conjures a magical spell upon "
    +"one of the sepulchers. The sepulcher falls silent for a brief "
    +"moment.\n");
    add_act("emote adjusts his ash-grey hooded robe with pale bony hands.");
    add_act("emote circles around the altar.");
    add_act("emote leers at the various sculptures.");
    add_act("emote grins with delight.");


    // All npc's must have this function.
    is_ravenloft_monster();

    set_exp_factor(XPFACTOR);

    arm_me();
}


mixed
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}


/*
* Function name: arm_me()
* Description  : Arms the NPC
*/
void
arm_me()
{
    object staff;

    seteuid(getuid(this_object()));

    staff = clone_object(DOMAIN_DIR + "droptables/martira_drops/r_eo_staff");
    staff->move(this_object());

    command("wear all");
    command("wield all");
}


/*
* Function name: do_die()
* Description  : Sets the items that this monster might drop.
*/
void
do_die(object killer)
{
    DROP_MASTER->certain_drop(EO_PRIEST_DROP, this_object());

	RAV_CONTROL_FULL->add_monsters_slain();

	MONEY_MAKE_SC(random(10) + 2)->move(this_object(), 1);
	MONEY_MAKE_GC(random(5) + 2)->move(this_object(), 1);
	MONEY_MAKE_PC(random(5) + 2)->move(this_object(), 1);

    ::do_die(killer);
}


