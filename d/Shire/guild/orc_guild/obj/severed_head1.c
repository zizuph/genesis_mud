/* 
	*Severed head base
	*Altrus, May 2005
	*changed to scalp, so as not to interfere 
	*with AoD guild(to be opened), June 2005
*/

inherit "/std/object";
#include <stdproperties.h>

#define DECAY_TIME (300.0)

static  int Decay_Alarm;        /* Alarm used when the flask decays */

void decay_this_object();

void create_object()
{
	set_name("scalp");
	set_pname("scalps");
	add_name("_head_for_standard");
	set_adj("bloody");
	add_prop(OBJ_I_WEIGHT, 75);
	add_prop(OBJ_I_VOLUME, 100);
	
	Decay_Alarm = set_alarm(30.0, 0.0, &decay_this_object());
}

void decay_this_object()
{
    object env = environment();

    tell_room(env, "The " + short() + " turns to dust and falls away.\n");	
    remove_object();
}