// file name:      /d/Avenir/common/dead/obj/paralyze_thief.c
// creator(s):     Lilith, July 2021              
// update history:
// purpose:        Paralyze for thieves who tried to steal from
//                 Mascarvin. There is no escaping death.
// note:           It only lasts for 5 minutes.
// bug(s):
// to-do:


inherit "/std/paralyze";
#include "/d/Avenir/common/dead/mascarvin/defs.h"

void
create_paralyze()
{
    set_name(PARA_ID);
	add_name("_Paralyzer");
	set_stop_object(previous_object());
	set_fail_message("There is nothing you can do but ponder what "
	    +"the goddess of death will do to you next.\n");
	set_remove_time(300);  // 5 minutes will seem like an eternity.
	set_stop_message("The icy grip around you relents.\n"
	    +"Feeling returns, and with it, intense pain.\n");
	set_stop_verb(0); //There is nothing they can do to stop it.
	
}

int
stop(string str)
{
	if (query_verb() == "drop")
		return 0;
	return ::stop(str);
}
		