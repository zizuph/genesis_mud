/* 
	*Orc food from corpses
	*Altrus, June 2005
*/

inherit "/std/food";
#include <stdproperties.h>

#define DECAY_TIME (1800.0)

static  int Decay_Alarm;        /* Alarm used when the flask decays */

void decay_this_object();

void
create_food()
{
	set_amount(50);
	add_prop(OBJ_I_WEIGHT, 75);
	add_prop(OBJ_I_VOLUME, 100);
	
	Decay_Alarm = set_alarm(DECAY_TIME, 0.0, &decay_this_object());
}

void decay_this_object()
{
    object env = environment();

    tell_room(env, "The " + short() + " turns to dust and falls away.\n");	
    remove_object();
}
