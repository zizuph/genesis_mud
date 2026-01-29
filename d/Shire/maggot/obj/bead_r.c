/*
	*One of the beads for Rosemary's necklace
	*Altrus, March 2005
*/

inherit "/std/object";
inherit "/cmd/std/command_driver";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

void create_object()
{
	set_name("bead");
	add_name("_r_bead");
	set_adj("small");
	set_adj("R");
	set_short("small R bead");
	set_long("This small bead has the letter 'R' carved on it.\n");
	
	add_prop(OBJ_I_WEIGHT, 5); 	
	add_prop(OBJ_I_VOLUME, 2);
	add_prop(OBJ_M_NO_STEAL, 0); 
	add_prop(OBJ_M_NO_DROP, "Don't drop it after you worked so hard to find it!\n");
	add_prop(OBJ_M_NO_GIVE, "No, on second thought you realize that you should probably do the work yourself.\n");

}


