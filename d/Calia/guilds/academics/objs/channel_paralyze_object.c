/*
 * Channel Paralyze Object
 * 
 * An Academic gains spells by channeling. While channeling, it will allow
 * will create a sequence of events but requires that they stay in place
 * and not move or do anything else.
 *
 * Created by Petros, December 2009
 */

#include <stdproperties.h>
#include <std.h>
#include <macros.h>
#include <files.h>

#include "../defs.h"

inherit "/std/paralyze";

#include "/d/Genesis/specials/debugger/debugger_tell.h"


// Variables
private static string * base_allow_verbs = ({
    "look",
    "l",
    "last",
    "mwho",
    "team",
    "who",
});
public string spell_to_learn;
public string * channel_messages = ({
    "You close your eyes and breathe slowly, harnessing your mind "
        + "for the task.",
    "You can sense your teacher's presence in your mind as he guides "
        + "you into a deep trance-like state.",
    "You feel a deep calm.",
    "Taking care you follow the instructions your teacher continues to give, "
        + "you start to move your hands as if holding an invisible round "
        + "object that must be constantly twirled and balanced.",
    "Continuing the circular motions with your hands and arms, you feel "
        + "elemental energies building in your fingertips!",
    "The energy continues to build!",
    "The hairs on your neck stand on end as you feel prickling sensations "
        + "start to consume your body.",
    "The prickling sensation flows through your entire body and pours "
        + "out into your outstretched arms.",
    "At your teacher's behest, you open your eyes and see before you a "
        + "shimmering globe of multicolored rays floating between your "
        + "hands!",
    "The teacher's voice fills your mind: Now!\nYou clasp your hands "
        + "together and the rays disperse into you.",
    "You feel you have learned something new!",
    });
    
public void
create_paralyze()
{
    set_name("_academic_channel_paralyze_object");
    add_name( ({ "academic_channel_paralyze_object" }) );
    set_short("hidden channel paralyze object");
    set_long("This is the hidden channel paralyze object that is on a "
        + "student who is channeling.\n");
    set_fail_message("You are too focused on the channeling to do "
        + "anything else! You could always <stop channeling> if you "
        + "need to.\n");
    
    // Set up the abort stuff
    set_stop_verb("stop"); 
    set_stop_fun("stop_channeling"); 
    set_stop_object(this_object());      
}

public void
set_spell_to_learn(string spell)
{
    spell_to_learn = spell;
}

public string
query_spell_to_learn()
{
    return spell_to_learn;
}

public string *
query_allowed_verbs()
{
    string * allow_verbs = ({ });

    allow_verbs += base_allow_verbs;
    allow_verbs += m_indices("/cmd/live/info"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/state"->query_cmdlist());
    
    return allow_verbs;
}

int
stop(string str)
{       
    // We want to allow some basic commands
    if (IN_ARRAY(query_verb(), query_allowed_verbs()))
    {
        return 0;
    }
    
    return ::stop(str);
}

public int
stop_channeling(string str)
{
    if (!strlen(str) || str != "channeling")
    {
        // returning 1 ensures the paralyze stays.
        return 1;
    }
    
    object player = this_player();
    // Return 0 to remove the paralyze object
    write("You force yourself to stop channeling. Samoht looks a "
        + "bit disappointed but largely ignores you to focus on "
        + "the rest of his class.\n");
    tell_room(environment(player), QCTNAME(player) + " decides to "
        + "leave the channeling class.\n", ({ player }));
    return 0;
}

public void
display_channel_message()
{
    object player = environment(this_object());
    if (!IS_PLAYER_OBJECT(player))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
    
    string message = channel_messages[0];
    channel_messages = channel_messages[1..];
    write("\n" + message + "\n\n");
    if (sizeof(channel_messages))
    {
        // Set up random intervals between 2 and 5 seconds
        float delay = itof(3 + random(5));
        set_alarm(delay, 0.0, &display_channel_message());
    }
    else
    {
        set_alarm(0.0, 0.0, remove_object);
        switch (spell_to_learn)
        {
        case "pyrofosti":
            ACADEMIC_MANAGER->set_acquired_fire_spell(player);
            break;
            
        case "hydrokine":
            ACADEMIC_MANAGER->set_acquired_water_spell(player);
            break;
            
        case "cheiropoto":
            ACADEMIC_MANAGER->set_acquired_elemental_spell(player);
            break;
            
        case "lithodermu":
            ACADEMIC_MANAGER->set_acquired_earth_spell(player);
            break;    
        
        default:
            return;
        }
        
        player->catch_tell("You have learned the " + spell_to_learn
            + " spell. See <help academic " + spell_to_learn + "> for "
            + "more information.\n");   
        tell_room(environment(player), QCTNAME(player) + " completes the "
            + "channeling class and seems to have learned something new!\n",
            ({ player }));         
    }
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    if (!IS_PLAYER_OBJECT(dest))
    {
        return;
    }
    
    set_alarm(0.0, 0.0, &display_channel_message());
}

