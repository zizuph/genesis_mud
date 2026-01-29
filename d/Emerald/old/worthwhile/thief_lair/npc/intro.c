/*
 *  Slightly modified version of /d/Genesis/lib/intro.c
 *  Allows certain NPCs in the bandits lair to introduce themselves when
 *  introed to.
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>

/*
 * Function name: greetings 
 * Description:   This function makes the npc do a greeting to people it
 *                allready know and to fellow npc's. 
 * The greeting depends upon whether or not the indidividual is a friend
 * or foe of the bandits.
 *
 * Arguments:     object who - the living that introduced to me
 *
 */
public void
greet(object who)
{
    command("bow " + OB_NAME(who));
    command("say Greetings " + who->query_name() + "!");
}

/*
 * Function name:       introduce
 * Description:         This function makes the npc do an introduction to a
 *                      player that has not been introed to it earlier.
 * Arguments            object who - the livint that introduced tome
 *
 */
public void
introduce(object who)
{
    command("introduce myself to " + OB_NAME(who));   
} 


void
add_introduced(string name)
{
    object who = find_player(name);

    if (!who || !present(who, environment(this_object())))
    {
        return;
    }

    if (this_object()->query_prop(LIVE_I_NEVERKNOWN) ||
        who->query_met(this_object()))
    {
        greet(who);
    }
    else
    {
        introduce(who);
    }
}
