/* 
	*bloody mass, cloned when the skull club pulps someone to death
	*Altrus, July 2005
*/

inherit "/std/object";
#include <stdproperties.h>

#define DECAY_TIME (500.0)

static  int Decay_Alarm;        /* Alarm used when the flask decays */

void decay_this_object();

void create_object()
{
	set_name("mass");
	set_pname("masses");
	set_adj("unrecognizable");
	set_adj("bloody");
	set_short("unrecognizable bloody mass");
	set_pshort("unrecognizable bloody masses");
	set_long("Simply put, this is a grotesque mass of meat, bone, and blood... lots of blood.\n");
	add_prop(OBJ_I_WEIGHT, 5000);
	add_prop(OBJ_I_VOLUME, 1000);
	add_prop(OBJ_M_NO_GET, "As much fun as carrying around a mass of blood and gore might be, it simply wont stay in one piece, no matter how you try to pick it up.\n");
	
	Decay_Alarm = set_alarm(DECAY_TIME, 0.0, &decay_this_object());
}

void decay_this_object()
{
    object env = environment();

    tell_room(env, "The " + short() + " dries up and crumbles away to nothing.\n");	
    remove_object();
}