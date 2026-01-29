/*   This is the Shire's Standard Monster to be inherited by all monsters
 *   in the Shire.
 *
 *   Copyright (C) Chad Richardson, Feb 97
 *
 *   Some handy functions when making monsters:
 *
 *   set_introduce(1);  Make the npc intro back to players
 *
 *   add_equipment(filenames); Adds equipment to the npc and makes them 
 *                             wield and wear items.
 */
#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <filter_funs.h>
#include "/d/Shire/sys/defs.h"

inherit "/std/monster";

//  Protoypes
void arm_shire_npc();
int introduce_me(string who);

static object gWep_func, gArm_func;
static int gWep_patch = 0;
static int Intro_me = 0;
static mixed *gFilenames = ({});

void
create_shire_monster()
{
}

void
create_monster()
{
    create_shire_monster();	
}

/*
 * Function name: query_introduce
 * Description:   To see if an npc introduces themselves or not?
 * Returns:       1/0 - does this npc introduce or not?
 */
int
query_introduce()
{
    return Intro_me;
}

/*
 * Function name: set_introduce
 * Description:   Set this npc up to intro by setting this function to 1
 * Arguments:     val - the val you wish to set the intro_me var to
 */
void
set_introduce(int val)
{
    Intro_me = val;
}

/*
 * Function name: introduce_me
 * Description:   introduces the npc back a player.
 *
 *                If you want the npc to intro differently then just
 *                redefine this function in your npc
 * 
 * Arguments:     who - the name of who we introduce back to
 * Returns:  1 if we introduced  0 if we couldn't find who to intro to.
 */
public int
introduce_me(string who)
{
    who = lower_case(who);
    if (!interactive(present(who,ENV(TO))))
	return 0;

    command("introduce myself to "+ who);
    return 1;
}

/*
 * Function name: add_introduced
 * Description:   Called when something introduces themselves, a good
 *                way to make an npc re-act to the introduce 
 * Arguments:     who - the name of who introduced themselves
 */

public void
add_introduced(string who)
{
    if (Intro_me)
	set_alarm(2.0,0.0,&introduce_me(who));
}

/*
 * Function name: add_equipment
 * Description:   Adds equipment to Npcs.
 * Arguments:     filenames - An array of filenames of the equipment
 *                            we want to clone.
 */
void
add_equipment(mixed filenames)
{
    if (stringp(filenames))
	filenames = ({filenames});
    if (!sizeof(filenames))
	return;
    gFilenames = filenames;
    if (environment(this_object()))
	arm_shire_npc();
}

void
arm_shire_npc()
{
    if (!sizeof(gFilenames))
	return;
    setuid(); seteuid(getuid());
    map(gFilenames, clone_object)->move(this_object());
    command("wield all");
    command("wear all");
    gFilenames = ({});
}

void
enter_env(object env, object from)
{
    ::enter_env(env,from);
    if (!objectp(from))
	arm_shire_npc();
}

/* The Wield and Wear functions taken directly from Krynn's std/monster */
/* With Lord Teth's Permision */

/*
 * Function name: wield
 * Description:   Called from the weapon the NPC is trying to
 *                wield. The purpose of the function is to
 *                remove the standard wield messages.
 * Arguments:     wep - The weapon to wield.
 * Returns:       True or the result from other functions.
 */
public mixed
wield(object wep)
{
    mixed tmp;

    if (!gWep_patch)
    {
	gWep_patch = 1;
	gWep_func = wep->query_wf();

	if (stringp((tmp = ::wield(wep))))
	    gWep_patch = 0;
	else
	    wep->set_wf(TO);

	return tmp;
    }
    else
    {
	gWep_patch = 0;
	wep->set_wf(gWep_func);

	if ((!gWep_func) || (!(tmp = gWep_func->wield(wep))))
	    return 1;
	else
	    return tmp;
    }
}

/*
 * Function name: wear
 * Description:   Called from the armour the NPC is trying to
 *                wear. The purpose of the function is to remove
 *                the standard wear messages.
 * Arguments:     arm - The armour to wear,
 * Returns:       True or the result from other function.
 */
public mixed
wear(object arm)
{
    mixed tmp;

    arm->set_af(gArm_func);

    if ((!gArm_func) || (!(tmp = gArm_func->wear(arm))))
	return 1;
    else
	return tmp;
}

/*
 * Function name: wear_arm
 * Description:   Makes sure that 'wear' gets called, if
 *                the armour gets worn.
 * Arguments:     arm - The armour to wear.
 * Returns:       True or the result from ::wear_arm
 */
public mixed
wear_arm(object arm)
{
    mixed tmp;

    gArm_func = arm->query_af();

    if (!stringp((tmp = ::wear_arm(arm))))
	arm->set_af(TO);

    return tmp;
}
