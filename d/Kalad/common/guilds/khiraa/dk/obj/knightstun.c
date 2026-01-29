/* 
 * /d/Kalad/common/guilds/khiraa/dk/obj/knightstun.c
 * Purpose    : This is the stun object for the stun attack, 'bashstun' of the Death Knights.
 * Located    : Used for a special attack of the Death Knights
 * Created By : Sarr 12.Apr.97
 * Modified By: 
 */ 

inherit "/std/paralyze";
#include "/d/Kalad/defs.h"

/* The paralizing object for the Death Knights of the Khiraa */

void
set_standard_paralyze(string str)
{
    set_name("knightstun");
    add_prop(OBJ_I_INVIS,100);
    set_stop_verb("stopitdamit");
    set_stop_fun("my_stop");
    set_stop_object(previous_object());
    set_stop_message("You stop " + str + ".\n");
    set_fail_message("You are too stunned to do anything!\n");
    set_remove_time(5);
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
    player -> catch_msg("You shake your head a few times and feel ready to "+
    "move again.\n");
    tell_room(E(player),QCTNAME(player)+" shakes "+HIS(player)+" head a "+
    "few times and looks less dazed.\n",player);
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

