/*
 * A paperbag with peanuts in it.
 */
 
inherit "/std/container";
 
#include <stdproperties.h>
 
create_container()
{
	set_name("bag");
	set_short("bag");
	set_long("This is a quite little bag. It's especially made " +
		 "for nuts.\n");
	add_prop(CONT_I_WEIGHT, 10);
	add_prop(CONT_I_MAX_WEIGHT, 100000);
	add_prop(CONT_I_VOLUME, 5);
	add_prop(CONT_I_MAX_VOLUME, 500005);
	
	call_out("fill_bag",1);
}
 
int
fill_bag()
{
	object nuts;
 
	setuid();
	seteuid(getuid(this_object()));
 
	nuts = clone_object("/d/Dville/deinonychus/tmp/nut");
	nuts->set_heap_size(20000);
	nuts->move(this_object());
 
}
