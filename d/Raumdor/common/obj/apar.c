inherit "/std/paralyze";
#include "/d/Raumdor/defs.h"
/* Apparition paralyzing obj, Sarr */

void
set_standard_paralyze(string str)
{
    set_name("apar");
    add_prop(OBJ_I_INVIS,100);
    set_stop_verb("stopitdamit");
    set_stop_fun("my_stop");
    set_stop_object(previous_object());
    set_stop_message("You stop " + str + ".\n");
    set_fail_message("You are paralyzed and cannot do anything!\n");
    set_remove_time(50);
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
    object player = E(TO);
    player -> catch_msg("You regain your senses and stand up.\n");
    tell_room(E(player),QCTNAME(player)+" regains "+player->query_possessive()+
    " senses and stands up.\n",player);
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

