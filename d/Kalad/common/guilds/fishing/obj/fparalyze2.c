 /*****************************************************************************
*  /d/Kalad/common/guilds/fishing/obj/fparalyze2.c
*
*  Paralyze File: Stops Movement
*
*  Created June 2019, Greneth        
*
 *****************************************************************************/

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/paralyze";

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "/d/Kalad/common/guilds/fishing/defs.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"

 /*****************************************************************************
*  Pragma
 *****************************************************************************/
#pragma strict_types

 /*****************************************************************************
*  Function name: create_paralyze
*  Description  : Constructor for the paralyze
 *****************************************************************************/
public void
create_paralyze()
{
   set_name("_fishing_paralyze_object2_");
   add_name( ({ "fishing_paralyze_object2" }) );
   set_short("hidden fishing paralyze object2");
   set_long("This is the hidden paralyze object that is on player "
   + "for fishing #2.\n");
   set_fail_message("You are busy fishing, <stop fishing> to quit.\n");
	set_stop_fun("stop_fishing");
	set_stop_verb("stop");
	set_stop_message("You stop fishing.\n");
	set_combat_stop(1);
}

 /*****************************************************************************
*  Function name: query_allowed_verbs
*  Description  : Actions allowed while paralyzed
 *****************************************************************************/
public string *
query_allowed_verbs()
{
    string * allow_verbs = ({ });

    allow_verbs += m_indices("/cmd/live/info"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/state"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/speech"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/items"->query_cmdlist());
    allow_verbs += m_indices("/cmd/live/things"->query_cmdlist());

    return (allow_verbs);
}

 /*****************************************************************************
*  Function name: stop
*  Description  : stops paralyze
 *****************************************************************************/
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