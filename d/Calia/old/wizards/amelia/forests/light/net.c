/*
*  adapted by Amelia, for use in the Light Forest
*/

inherit "/std/weapon";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include <wa_types.h>

void
create_weapon()
{
	set_name("net");
	add_name("fishing net");
	set_adj(({"old", "dilapidated", "fishing"}));
	set_short("old fishing net");
	set_pshort("old fishing nets");
	set_long("This is an old dilapidated fishing net. "+
		"The handle is partially broken, and the net is a "+
		"bit torn, but it may still be somewhat serviceable.\n");

		
	set_default_weapon(3,3,W_POLEARM,W_BLUDGEON, W_BOTH);
	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_I_WEIGHT, 200);
	add_prop(OBJ_I_VOLUME, 200);
}


string
wep_condition_desc()
{
	return "It appears to be in fairly poor condition.\n";
}
