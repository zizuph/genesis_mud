inherit "/std/paralyze";
#include "/d/Raumdor/defs.h"
/* Ghoul paralyzing obj, Sarr */
/* Updated by Mirandus April 8, 2015 - Updated the stop message so that the
   grammar is more correct.*/

void
set_standard_paralyze(string str)
{
    set_name("ghoulp");
    add_prop(OBJ_I_INVIS,100);
    set_stop_verb("stopitdamit");
    set_stop_fun("my_stop");
    set_stop_object(previous_object());
    set_stop_message("You feel as though you can move again.\n");
    set_fail_message("You cannot move, you are paralyzed!\n");
    set_remove_time(30);
    add_prop(OBJ_M_NO_DROP,1);
    set_no_show();
}

/*
 * Function name: stop_paralyze
 * Description:	  This function is called if the paralyze shall stop due to 
 *		  the time running out.
 */
int my_stop()
{
    E(TO) -> catch_msg("You feel like you can move again.\n");
    return 0;
}

varargs void
stop_paralyze()
{
    if (stop_object && stop_fun)
	call_other(stop_object, stop_fun, environment(this_object()));
    else if (stop_message && environment(this_object()))
	environment(this_object())->catch_msg(stop_message);

    remove_object();
}

