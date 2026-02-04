/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * This is an NPC named "Remsal".  He is called by hotel.c, and exists
 * to serve and watch over the Hotel. If killed, the Hotel is useless.
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <const.h>
#include <ss_types.h>

/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    if (!IS_CLONE)
	return;

    ::create_monster();
    set_name("remsal");
    set_living_name("remsal");    
    set_race_name("human");
    set_adj("tall");
    set_long("It's a very tall human. He takes care of the lodging house.\n");

    default_config_npc(40);
    set_all_hitloc_unarmed(25);
    set_skill(SS_DEFENCE,      40);
    set_skill(SS_AWARENESS,    40);
    set_skill(SS_UNARM_COMBAT, 40);

    set_gender(G_MALE);
    add_prop(LIVE_I_QUICKNESS, 50);

    trig_new("%s 'introduces'  %s", "intro_me");
}

/*
 * Function name: intro_me
 * Description:   Trigger for introductions.  Set a call out to do the intro.
 * Arguments:     s1 - first string match (ignored)
 *                s2 - second string match (ignored)
 */
public void
intro_me(string s1, string s2)
{
    set_alarm(2.0, -1.0, "do_intro", s1);
}

/*
 * Function name: intro_me
 * Description:   called by trigger to make this npc intro himself.
 */
public void
do_intro(string s1)
{

    command("introduce myself");
    command("say greetings, " + s1 + "!");
}
