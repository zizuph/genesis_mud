/*********************************************************************
 * - deer.c                                                        - *
 * - This is a slice of roasted deer to be used in SaMorgan Inn    - *
 * - Created by Damaris 08/2006                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
	set_name("deer");
	set_adj(({"roasted"}));
	set_short("slice of roasted deer");
	set_pshort("slices of roasted deer");
	set_long("This is a slice of succulent roasted deer. It has "+
	"a been roasted to perfection with spices and wine.\n");
	set_amount(80);
	add_prop(HEAP_I_UNIT_VOLUME, 50);
	add_prop(HEAP_I_UNIT_VALUE, 30);
}
