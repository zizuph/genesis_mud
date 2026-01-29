/*********************************************************************
 * - wwine.c                                                       - *
 * - This is a glass of white wine to be used in SaMorgan Inn      - *
 * - Created by Damaris 08/2006                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
	set_name("wine");
	add_name(({"glass", "white wine"}));
	set_adj(({"glass", "white"}));
	set_short("glass of white wine");
	set_pshort("glassess of white wine");
	set_long("This is a glass of sparkling white wine. It has "+
	"been aged to perfection.\n");
	set_soft_amount(500);
	set_alco_amount(50);
	add_prop(HEAP_I_UNIT_VOLUME, 100);
	add_prop(HEAP_I_UNIT_VALUE, 100);
}
