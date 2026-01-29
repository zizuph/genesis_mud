/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/serpent.c
 *
 *  This snake teaches the player to fight, pre-creation.
 *
 *  Created May 2011, by Cooper Sherry (Gondor)
 */

#pragma strict_types

inherit "/std/monster";

#include <stdproperties.h>      /* for NPC_I_NO_LOOKS, etc      */


/* Prototypes */
public void     create_monster();
public int      special_attack(object victim);
public void     notify_death(object killer);


/*
 * Function name:       create_monster
 * Description  :       set up the guard
 */
public void
create_monster()
{
    set_name( ({ "serpent" }) );
    add_name( ({ "snake" }) );
    add_adj( ({ "shadow" }) );
    set_race_name("snake");

    set_short("shadow serpent");
    set_long("This menacing creature is blocking your way forward. You"
      + " must <kill> it before travelling onward.\n");

    default_config_npc(3);
    set_alignment(0);

    add_prop(CONT_I_WEIGHT, 81600);      /* 180 lbs */
    add_prop(CONT_I_HEIGHT, 125);        /* 70 inches */
    add_prop(CONT_I_VOLUME, 140000);     /* 8000 cubic inches */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1); /* chasing npcs is not fun! */

    set_act_time(20);
    add_act("emote hisses menacingly.");
    add_act("emote slithers back and forth.");
    add_act("emote peers at you with baleful eyes.");
    add_act("emote flicks its forked tongue in and out.");
} /* create_monster */


/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 */
public int
special_attack(object victim)
{
    victim->catch_msg(one_of_list( ({
        "The shadow serpent lunges at you, but misses!\n",
        "The shadow serpent throws its coiled body toward you,"
      + " missing only by inches!\n",
        "The fangs of the shadow serpent soar past your cheek, nearly"
      + " making contact!\n",
        "The shadow serpent bares its fangs, and darts to the side.\n",
        "The shadow serpent readies itself for a spring forward.\n",
        }) ));

    /* We do not want the player to face any true danger here, so this
     * is all for show. Always return 1 to prevent normal attacks.
     */
    return 1;
} /* special_attack */


/*
 * Function name: notify_death
 * Description:   Notify onlookers of the death, with a special message
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    if (living(killer))
    {
        tell_object(killer, 
            "You killed the shadow serpent.\n\n"
          + "Well done! You are now able to safely travel <north>.\n");
    }
}