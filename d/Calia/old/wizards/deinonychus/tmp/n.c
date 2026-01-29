/*
 * A peanut
 */
 
inherit "/d/Dville/deinonychus/tmp/foodheap";

#include <stdproperties.h>
 
create_object()
{
	set_amount(5);
	set_heap_size(20);
	set_name("nut");
	set_short("nut");
	set_pshort("nuts");
	set_long("It's one of the famous nuts of Spain.\n");
	add_prop(HEAP_I_UNIT_VOLUME, 25);
	add_prop(HEAP_I_IS, 1);
	add_prop(HEAP_I_UNIT_VALUE, 1);
	::create_object();
}
