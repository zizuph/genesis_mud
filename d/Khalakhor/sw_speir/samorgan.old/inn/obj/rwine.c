/*********************************************************************
 * - rwine.c                                                       - *
 * - This is a glass of red wine to be used in SaMorgan Inn        - *
 * - Created by Damaris 08/2006                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
	set_name("wine");
	add_name(({"glass", "red wine"}));
	set_adj(({"glass", "red"}));
	set_short("glass of red wine");
	set_pshort("glassess of red wine");
	set_long("This is a glass of red wine. It has been aged to "+
	"perfect.\n");
	set_soft_amount(500);
	set_alco_amount(50);
	add_prop(HEAP_I_UNIT_VOLUME, 100);
	add_prop(HEAP_I_UNIT_VALUE, 100);
}
