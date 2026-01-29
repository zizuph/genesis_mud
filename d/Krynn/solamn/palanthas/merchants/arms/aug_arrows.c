/*
 * Mortis 04.2006
 * 
 * Arrows fletched and sold by Aug, Bowyer of Palanthas.
 *
 */

#include </stdproperties.h>
#include "../../local.h";

inherit "/std/arrow";
inherit "/lib/keep";

string
get_projectile_long(string str, object for_obj, int num)
{
    return "Grey-feathered with a pale, natural finished shaft, the arrow"
	+ ((num == 1) ? " is" : "s are") + " steel-tipped with thin, bronze "
	+ "edges sharp as razors.\nA small \"A\" has been stamped into "
	+ ((num ==1) ? "its shaft" : "their shafts") + ".\n";
}

void
create_arrow()
{
	set_adj("bronze-edged");
	add_adj("grey");
	set_projectile_id("aug_arrow");

	set_heap_size(10);
	set_hit(40);
	set_pen(40);
	set_keep(1);
}
