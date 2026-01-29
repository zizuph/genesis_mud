/**
* Coded by Louie 2004
* 
* Object to keep track of if someone is in the middle of 
* building an explosive device.
*
*/
#pragma strict_types

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

void
create_object()
{
	
    set_name("constructing_ob");
    set_short("constructing_ob");
    add_name("_gnome_constructing_ob");
    set_adj("constructing");
    set_long("This object is used to keep someone from constructing "+
    	"more than one object at a time.  It should remove itself " +
    	"after a minute (constructing an object should only take about "+
    	"20-30 seconds.\n");
    
    set_no_show();
   	set_alarm(60.0, 0.0, "remove_object");
	
	add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);
    
    
}



