/*********************************************************************
 * - ccake.c                                                       - *
 * - This is a sweet coffee cake to be used in SaMorgan Inn        - *
 * - Created by Damaris 08/2006                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
	set_name("cake");
	set_adj(({"sweet", "coffee"}));
	set_short("piece of coffee cake");
	set_pshort("pieces of coffee cake");
	set_long("This is a piece of swirled coffee cake. It has a sweet "+
	"white icy dripping along the sides of it. It is warm and moist "+
	"and compliments a cup of coffee perfectly.\n");
	set_amount(50);
	add_prop(HEAP_I_UNIT_VOLUME, 30);
	add_prop(HEAP_I_UNIT_VALUE, 50);
}
