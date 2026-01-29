/*
 * An packadge for introducing NPC's made by Rohim because I am so fucking
 * tired of fixing all those ugly constructions with triggers.
 * Copyright (C) 1996, Andreas Jonasson (Rohim)
 *
 */

#pragma strict_types
#include <stdproperties.h>

/*
 * Function name: greetings 
 * Description:   This function makes the npc do a greeting to people it
 *                allready know and to fellow npc's. It is possible to
 *                redefine, not however that it should never contain an
 *                'introduce myself' command.
 * Arguments:     name: The name of the person that introduces himself.
 *
 */
public void
greet(string name)
{
    command("bow " + name);
    command("say Greetings " + capitalize(name) + "!");
}

/*
 * Function name:       introduce
 * Description:         This function makes the npc do an introduction to a
 *                      player that has not been introed to it earlier. The
 *                      function may be redefined to create varity.
 * Arguments            name: The name of the person that introduces himself.
 *
 */
public void
introduce(string name)
{
    command("introduce myself");
    command("say Well met " + capitalize(name) + "!");
} 


void
add_introduced(string name)
{
    if (this_player()->query_npc() ||
        this_object()->query_prop(LIVE_I_NEVERKNOWN) ||
        this_player()->query_met(this_object()))
        greet(name);
    else
        introduce(name);
}
