//-*-C++-*-
// file name:   /d/Avenir/inherit/leftover.c 
// creator(s):  Lilith 
// revised:
// purpose:     A pointer to the /std/leftover, with the addition of
//              some props to make leftovers acceptible as offerings
//              to certain gods.      
// note:        Just add the *_OFFERING prop for the relevant gods to
//              the create_leftover, below. 
//      To add leftovers to npcs : 
//      add_leftover("/d/Avenir/inherit/leftover", "hand",1, "", 0,0);
// or   add_leftover("/d/Avenir/inherit/leftover", "heart",1, "", 0,0);
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/leftover";

#include <language.h>
#include "/d/Avenir/include/deities.h"
static private int decay_alarm;

public void
create_leftover()
{
    add_prop(ACLOLTHAYR_OFFERING, 1);
    add_prop(JAZUR_OFFERING, 1);
     ::create_leftover();
}


/*
 * Function name: decay_fun
 * Description  : Decays the leftover after a predefined period of time when
 *                the leftover is dropped in a room.
 */
public void
decay_fun()
{
    if (--decay_time)
    {
	decay_alarm = set_alarm(60.0, 0.0, decay_fun);
    }
    /* With skins, let's be nice to the Smiths. */
    if (id("skin"))
    {
        tell_room(environment(this_object()),
	    capitalize(LANG_THESHORT(this_object())) +
            ((num_heap() == 1) ? " has" : " have") +
	    " hardened into a piece of leather.\n");
        seteuid(getuid());
        clone_object("/d/Shire/guild/smiths/obj/sm_leath")->move(environment(this_object()), 1);
        remove_object();            
    }
    else
    {
        tell_room(environment(this_object()),
	    capitalize(LANG_THESHORT(this_object())) +
            " rapidly " + ((num_heap() == 1) ? "decays" : "decay") +
	    ".\n");
	remove_object();
    }
}
