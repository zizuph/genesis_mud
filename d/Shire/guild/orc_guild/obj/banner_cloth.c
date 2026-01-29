/*
	*Prepared cloth for banner making
	*Altrus, May 2005
*/

inherit "/std/object";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

void create_object()
{
	set_name("cloth");
	set_pname("cloths");
	add_name("_a_cut_cloth");
	set_adj("plain");
	set_adj("ragged");
	set_short("plain ragged cloth");
	set_pshort("plain ragged cloths");
	set_long("This the chopped and ragged remains of some garment or clothing.\n");
	
	add_prop(OBJ_I_WEIGHT, 250); 	
	add_prop(OBJ_I_VOLUME, 50);
}


