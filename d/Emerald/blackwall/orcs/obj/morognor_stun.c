/* This object is passed to victims of Morognor's stunning shield
   charge. It paralyzes them for a few seconds.
   Code (c) 2000 to Damian Horton, BKA Casimir.
*/

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/paralyze";

void
create_paralyze()
{
    set_name("_stun");
    set_short("Morognor stun object"); //for the benefit of wizards

    add_prop(OBJ_S_WIZINFO, "This is a standard paralyze object passed to "+
			  "people struck by Morognor's "+
			  "(/d/Emerald/blackwall/orcs/npc) "+
			  "shield charge special.\n");

    set_fail_message("You cannot gather your thoughts sufficiently to "+
		     "do that right now.\n");
    set_stop_message("You recover your senses.\n");
    
}





