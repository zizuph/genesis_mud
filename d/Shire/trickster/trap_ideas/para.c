inherit "/std/paralyze";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/trickster/trickster.h"

public void
create_paralyze()
{
    set_name("paralyze");
    add_name("_trickster_paralyze");
    set_stop_fun("abandon_trap");
    set_stop_object(TO);
    set_stop_verb("stop");
    set_fail_message("You can't do that since you are currently busy "+
      "setting up your trap.  Type 'stop' to quit setting it up.\n");
}

nomask public int
abandon_trap()
{
    if (!objectp(environment()))
    {
	remove_object();
	return 1;
    }

    set_this_player(environment());

    TP->catch_msg("You abandon making your trap!\n"); 
    TP->remove_prop(TRICKSTER_TRAP_TYPE);
    say(QCTNAME(TP)+" abandons setting up "+HIS_HER(TP)+" trap.\n");
    return 0;
}

nomask public void
stop_paralyze()
{
    remove_object();
}


