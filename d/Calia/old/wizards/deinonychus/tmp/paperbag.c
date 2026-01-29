/*
 * A paperbag with peanuts in it.
 */
 
inherit "/std/container";
 
#include <stdproperties.h>

create_container()
{
	set_name("paperbag");
	set_short("paperbag");
	set_long("This is a quite little paperbag. It's especially made " +
		 "for peanuts.\n");
	add_prop(CONT_I_WEIGHT, 10);
	add_prop(CONT_I_MAX_WEIGHT, 110);
	add_prop(CONT_I_VOLUME, 1);
	add_prop(CONT_I_MAX_VOLUME, 501);
	add_prop(CONT_I_WEIGHT, 10);
	
	call_out("fill_bag",1);
}
 
int
fill_bag()
{
	int i;
	object peanut;
	
	for(i=0; i < 20; i++)
	{
		peanut = clone_object("/d/Dville/deinonychus/peanut");
		peanut->move(this_object());
	}
}
