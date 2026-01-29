/* -*- C++ -*- */

/*
 * Terel standard monster
 *
 * All the monsters in the domain should inherit this one.
 * Code to handle intros based on Mercade's tutorial.
 */

#include "/d/Terel/include/Terel.h"

inherit "/std/monster";
inherit "/d/Terel/std/living_extra";

/*
 * Prototypes
 */

void introduce_me(object who);

/*
 * Global Variables
 */

/*
 * Function name: enable_intro
 * Description  : set a property that will enable this monster to
 *                react to introductions.
 */
public void
enable_intro()
{
    if (!(TO->query_prop(LIVE_I_INTRO_ENABLED)))
        TO->add_prop(LIVE_I_INTRO_ENABLED, 1);
}

/*
 * Function name: disable_intro
 * Description  : set a property that will disable this monster to
 *                react to introductions.
 */
public void
disable_intro()
{
    if (TO->query_prop(LIVE_I_INTRO_ENABLED))
        TO->remove_prop(LIVE_I_INTRO_ENABLED);
}

int last_introduction = 0;

/*
 * Function name: add_introduced
 * Description  : Whenever someone is introduced to me (CC), this function
 *                is called in me to tell me that 'name' (BB) is being
 *                introduced to me. The living that does the introduction
 *                (AA) is available though this_player().
 * Arguments    : string name - the [lower case] name of the living that
 *                              is being introduced to me. (BB)
 */
public void
add_introduced(string name)
{
    /* In players, this function makes sure that 'name' appears on your
     * 'introduced' list and then you may later 'remember' him/her. In
     * NPC's you may for instance use it to return the honour by
     * introducing yourself. Note that we don't necessarily have to use
     * an alarm since this function is called _after_ all messages from
     * the original introduction have been printed.
     */

    object who;

    if (!(TO->query_prop(LIVE_I_INTRO_ENABLED))) {
	return;
    }
    
    if ((who = present(name, ETO)) == 0) {
	return;
    }

    if (!who || (ETO != ENV(who))) {
	return;
    }

    if (!(who->query_met(TO))) {
	introduce_me(who);
    }
}

/*
 * Function name: introduce_me
 * Description  : called when an introduction is to be performed.
 * Arguments    : string name - the [lower case] name of the living that
 *                              is being introduced to me. (BB)
 */
public void
introduce_me(object who)
{
    TO->command("introduce me to " + who->query_real_name());
}

/*
 * Handle intros
 *
 *  trig_new("%s 'introduces' %s", "react_introduce");
 *
 */

return_introduce(string who)
{
    object *obs;
    string name, dummy;
    if ((last_introduction + 10) > time())
	return;

    last_introduction = time();

    TO->command("introduce myself to " + who);
}
