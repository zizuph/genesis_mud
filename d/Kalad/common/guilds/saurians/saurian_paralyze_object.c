/*
 * Saurian Join Paralyze
 * 
 * Briefly Paralyzes a player while they are joining the Saurian
 * racial guild. Don't want them walking out during the join story
 * and messing stuff up.
 *
 * Created by Mirandus, February 2018
 */

#include <stdproperties.h>
#include <std.h>
#include <macros.h>

#include "lizards.h"

inherit "/std/paralyze";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Variables
private static string * base_allow_verbs = ({
    "emote",
    "forget",
    "introduce",
    "introduced",
    "invite",
    "join",
    "last",
    "leave",
    "mwho",
    "present",
    "remember",
    "remembered",
    "stop",
    "team",
    "who",
});

public void
create_paralyze()
{
    set_name("_saurian_join_paralyze_object_");
    add_name( ({ "saurian_join_paralyze_object" }) );
    set_short("hidden charge paralyze object");
    set_long("This is the hidden paralyze object that is on player "
        + "joining the Saurian Racial Guild.\n");
    set_fail_message("You are in too much pain to do anything else.\n");
}

public string *
query_allowed_verbs()
{
    string * allow_verbs = ({ });

    allow_verbs += base_allow_verbs;
    allow_verbs += m_indices("/cmd/live/info"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/state"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/speech"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/items"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/things"->query_cmdlist());

    return (allow_verbs);
}

int
stop(string str)
{       
  
    // We want to allow also some basic commands
    if (IN_ARRAY(query_verb(), query_allowed_verbs()))
    {
        return 0;
    }
    
    return ::stop(str);
}
