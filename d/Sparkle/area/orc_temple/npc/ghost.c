/*
 *  /d/Sparkle/area/orc_temple/npc/ghost.c
 *
 *  These creatures are the remnants of the souls that have been
 *  torn into pieces by the demon. They carry the important
 *  ghost tears that are important for one of the enchanter quests.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";

#include <const.h>
#include <filepath.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include "../defs.h"

/* Definitions */
#define            VANISH_DELAY           120.0

/* Prototypes */
public void        create_monster();
public void        dematerialize();

/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster()
{
    set_race_name("unknown");
    set_name("spirit");
    add_name( ({ "ghost" }) );
    add_adj( ({ "dead", "undead" }) );

    set_short("spirit of the dead");
    set_long("Vaguely reminiscent of a humanoid form, this spirit of"
      + " the dead looks horribly stretched and torn - filled with"
      + " untold anguish and pain.\n");

    set_gender(G_NEUTER);

    set_alignment(0); /* no alignment - a mindless creature */
    set_stats( ({ 5, 20, 10, 30, 30, 40 }) );
                  
    set_skill(SS_AWARENESS,    100);
    set_skill(SS_DEFENCE,      10);
    set_skill(SS_UNARM_COMBAT, 20);

    add_item( ({ "spirit of the dead" }), long);

    set_act_time(4);
    add_act("emote moans softly.");
    add_act("emote shudders with pain.");
    add_act("emote whispers: I ... was ... !");
    add_act("emote whispers: Yog ... So ... Thoth ...");
    add_act("emote floats around the edges of the room.");
    add_act("wail");
    add_act("emote peers at you, and a horribly twisted face suddenly"
      + " snaps into focus before again fading into obscurity.");
    add_act("emote fades from view momentarily, and then reappears.");
    add_act("emote whispers: Pit ... the pit ... the pit ...");

    add_cact("emote swirls around you!");
    add_cact("emote whispers: Yog ... So ... Thoth ...");
    add_cact("emote passes its matter through your body, chilling"
      + " every point of flesh.");
    add_cact("emote whispers: Thoth! ... Thoth!");

    add_prop(LIVE_I_UNDEAD, 1);    /* It is quite undead.  */
    add_prop(LIVE_I_NO_CORPSE, 1); /* No corpse upon kill. */

    set_aggressive(1, 100); /* deranged, fearless, attacks anyone */

    setuid();
    seteuid(getuid());

    set_alarm(VANISH_DELAY, 0.0, &dematerialize());
} /* create_monster */


/*
 * Function name:   query_gender
 * Description:     Returns the gender code of the living.
 * Returns:         The code. (0 - male, 1 - female, 2 - netrum)
 */
public int
query_gender()
{
    return G_NEUTER;
}


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death,
 *                though in this case, we do not want a death,
 *                but merely a defeat.
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    string  desc = one_of_list( ({ "female", "male" }) ) + " "
                 + one_of_list( ({ "gnome", "dwarf", "human", "elf" }) );
    object  tear;
    object  here = environment(this_object());
    object *summoners = FILTER_PLAYERS(all_inventory(
                            environment(this_object())));

    tell_room(environment(this_object()),
        QCTNAME(this_object()) + " shudders momentarily, and then"
      + " begins to collapse inward. For a brief moment, the peaceful" 
      + " face of a " + desc + " emerges from the spirit form. A gleaming"
      + " crystalline tear falls from the face just before it fades and is"
      + " gone.\n");

    if (living(killer))
    {
        tell_object(killer, 
            "You released the spirit.\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " released " +  query_objective() + ".\n",
           ({ this_object(), killer }));
    }

    tear = clone_object(OBJ_DIR + "ghost_tear");
    tear->move(environment(this_object()));

    foreach(object summoner: summoners)
    {
        environment(this_object())->set_summonings(
            summoner->query_real_name());
    }

#if LOG_ACTIVITY
        write_file(LOG_DIR + "ghost", 
            TIME2FORMAT(time(), "mm/dd/yyyy")
          + " (" + ctime(time())[11..18] + ") "
          + capitalize(this_player()->query_name())
          + " kills a ghost in " + FILE_NAME(MASTER_OB(here)) + ".\n");
#endif
} /* notify_death */


/*
 * Function name:        dematerialize
 * Description  :        have the ghosts dematerialize after a
 *                       while
 */
public void
dematerialize()
{
    if (!query_relaxed_from_combat())
    {
        set_alarm(VANISH_DELAY, 0.0, &dematerialize());
        command("emote shimmers slightly.");
        return;
    }

    command("emote dematerializes with a long wailing moan.");
    remove_object();
} /* dematerialize */