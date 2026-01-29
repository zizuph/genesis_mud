/*
 *  Fishing paralyse object when fishing rod post cast, allows reeling. 
 *  Based on /w/greneth/fishing/obj/fparalyze.c by Greneth.
 * 
 *  Arman, March 2021
 */
 
#pragma strict_types

#include <macros.h>

inherit "/std/paralyze";

// Variables
private static string * base_allow_verbs = ({ "reel", });

public void
create_paralyze()
{
    set_name("_fishing_paralyze_object_");
    add_name( ({ "fishing_paralyze_object", "fishing_reeling_paralyze_object" }) );
    set_short("hidden fishing paralyze object");
    set_long("This is the hidden paralyze object that is on player "
        + "for fishing.\n");
    set_fail_message("You are busy fishing <stop fishing> to quit.\n");
	set_stop_fun("stop_fishing");
	set_stop_verb("stop");
	set_stop_message("You stop fishing.\n");
	set_combat_stop(1);
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