
/*
 * Child manadala invisible object
 * No value
 * Only used for mandala creation
 * This proves they are on the task to
 * create their child mandala
 */
 
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

public int task_status;

void 
create_object() 
{
    set_name(EC_CHILD_MANDALA_TASK);
    add_name("invismandala");
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_STEAL,1);
    set_no_show(); /* invisible to player */
}

void
set_task_status(int value)
{
	task_status = value;
}

int
query_task_status()
{
	// Possible legitimate values
	//  0 - Just started the task, needs to pray to the Five in Obelisk Garden
	//  1 - Needs to rub dirt on Gu Obelisk
	//  2 - Needs to pour water on Diabrecho Obelisk
	//  3 - Needs to breathe on Aeria Obelisk
	//  4 - Needs to ignite Pyros Obelisk
	//  5 - Needs to stab hand with Ceremonial Dagger
	//  6 - Needs to talk to Jardeth about Seed Pod
	//  7 - Needs to plant sporos seed in herb garden and water with vial
	// 71 - Planted the sporos seed and needs to water with vial
	//  8 - Needs to talk to Arial about Crystalline Seed (or Sporos)
	//  9 - Needs to plant crystalline seed in Earth's Behold and pour vial on it
	// 91 - Planted crystalline seed and needs to pour vial on it
	// 10 - Needs to talk to Tahla about Seed Gem (or Sporos)
	// 11 - Needs to prepare powder for Tiashe
	// 12 - Needs to sprinkle powder on Seed Gem
	// 13 - Needs to talk to Sehis about Seed Gem (or Sporos or Blessing)
	
	return task_status;
}

public string
query_auto_load()
{
    return MASTER + ":" + task_status;
}

public void
init_arg(string arg)
{
    task_status = atoi(arg);
}