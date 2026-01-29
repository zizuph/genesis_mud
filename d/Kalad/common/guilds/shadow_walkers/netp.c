inherit "/std/paralyze";
#include "/d/Kalad/defs.h"
/*  Sarr */

void
set_standard_paralyze(string str)
{
    set_name("netp");
    add_prop(OBJ_I_INVIS,100);
    set_stop_verb("stopitdamit");
    set_stop_fun("my_stop");
    set_stop_object(previous_object());
    set_stop_message("You stop " + str + ".\n");
    set_fail_message("You cannot move, you are all tangled up in the net!\n");
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
    object me = E(TO);
    tell_room(E(me),QCTNAME(me)+" finally breaks away from the "+
    "net and casts it to the ground.\n",me);
    me->catch_msg("You finally break away from the net and "+
    "cast it to the ground!\n");
    clone_object("/d/Kalad/common/guilds/shadow_walkers/net")->move(E(E(TO)));
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

