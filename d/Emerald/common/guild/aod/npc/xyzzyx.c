/*
 *  /d/Emerald/common/guild/aod/npc/xyzzyx.c
 *
 *  This is Xyzzyx, the Darkling who presides over the Army of Darkness
 *  guild. He is a fearsome magical foe.
 *
 *  Created May 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/darkling";

#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <time.h>

/* Definitions */
#define            BADNESS_LOG  (AOD_LOG_DIR + "darkling_zap")

/* Prototypes */
public void        create_darkling();
public void        add_introduced(string name);
public void        react_intro(object tp);
public void        return_object(object obj, object to);
public void        zap_everyone();
public int         special_attack(object victim);


/*
 * Function name:        create_darkling
 * Description  :        set up the npc
 */
public void
create_darkling()
{
    set_living_name("Xyzzyx");
    set_name("xyzzyx");
    set_adj( ({ "gleaming", "electric-eyed" }) );

    set_title("the Ascended, Practitioner of the Second Circle of"
      + " Power");

    set_long("Every inch of flesh on the naked body of this small"
      + " being is inky black, and gleams like smooth porcelain. Though"
      + " less than three feet tall, there is a power radiating from"
      + " him. His eyes crackle and pulse with bright pink energy,"
      + " appearing almost as burning flares from his tiny round"
      + " head. He is sitting cross-legged, floating in mid-air.\n");

    set_act_time(10);
    add_act("emote floats slightly lower to the ground, narrowing"
      + " his electric pink eyes in contemplation.");
    add_act("emote extends his hands apart, sending arcs of purple"
      + " lightning shooting between his two outstretched palms.");
    add_act("emote closes his eyes suddenly, and appears to be"
      + " concentrating on some far-distant matter.");
    add_act("emote peers directly at you. The lack of pupils in his"
      + " electric pink eyes makes it hard to tell if he is focusing"
      + " on you, or just looking in your direction.");

    set_stats( ({ 40, 140, 120, 200, 200, 140 }) );

    remove_prop(LIVE_I_NEVERKNOWN);
} /* create_darkling */


/*
 * Function name:       add_introduced
 * Description  :       Add the name of a living who has introduced to us
 * Arguments    :       string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond
     */
    if (interactive(this_player()) &&
        CAN_SEE_IN_ROOM(this_object()) &&
        CAN_SEE(this_object(), this_player()) &&
        (!this_player()->query_met(query_name()) ||
         this_player()->query_wiz_level()))
    {
        set_alarm(2.0, 0.0, &react_intro(this_player()));
    }
} /* add_introduced */


/*
 * Function name:        react_intro
 * Description  :        respond to introduction
 * Arguments    :        object tp -- the person who intro'd
 */
public void
react_intro(object tp)
{
    if (environment(tp) != environment())
    {
        command("emote peers around quizzically.");
        return;
    }

    command("introduce me");

} /* react_intro */


/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    command("emote looks at you in annoyance.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * We don't want people giving him random crap.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    set_alarm(0.5, 0.0, &return_object(ob, from));
} /* enter_inv */


/*
 * Function name:        zap_everyone
 * Description  :        Have the Darkling use horrible magic against
 *                       all foes in the room.
 */
public void
zap_everyone()
{
    int     i,
            damage_level = 400 + random(1000);
    mixed  *target = filter(all_inventory(environment(this_object())),
                         &operator(==)(, this_object()) @
                         &->query_attack());

    command("emote pauses, and his eyes flash.");
    tell_room(environment(this_object()), "Purple energy lashes"
      + " across the ground, searing everything in its path!\n");

    for (i = 0; i < sizeof(target); i++)
    {
        target[i]->catch_tell("You are horribly burned by the"
          + " purple energy!\n");
        target[i]->command("$wail");
        target[i]->heal_hp(0 - damage_level);

        if (!target[i]->query_npc())
        {
            write_file(BADNESS_LOG,
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(target[i]->query_name()) + " takes "
              + damage_level + " damage from the Darkling Zap!\n");
        }

        if (target[i]->query_hp() == 0)
        {
            target[i]->do_die();
            if (!target[i]->query_npc())
            {
                write_file(BADNESS_LOG,
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
                  + ctime(time())[11..18] + ") "
                  + capitalize(target[i]->query_name())
                  + " was killed by"
                  + " the Darkling Zap!\n");
            }
        }
    }
} /* zap_everyone */


/*
 * Function name:        special_attack
 * Description  :        set up the specials for the Darkling
 * Arguments    :        victim (the one we are fighting right now)
 * Returns      :        0 - if we want the round to continue
 *                       1 - if we are done with this round
 */
public int
special_attack(object victim)
{
    if (!random(5))
    {
        zap_everyone();
        return 1;
    }

    return 0;
} /* special_attack */
