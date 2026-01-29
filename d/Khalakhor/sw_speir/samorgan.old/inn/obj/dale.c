/*********************************************************************
 * - dale.c                                                        - *
 * - This is a dark ale to be used in SaMorgan Inn                 - *
 * - Created by Damaris 08/2006                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
	set_name("ale");
	add_name(({"mug", "dark ale"}));
	set_adj(({"mug", "dark"}));
	set_short("mug of dark ale");
	set_pshort("mugs of dark ale");
	set_long("This is a mug of very dark ale. It has been fermented "+
	"quite well and has a nice head of foam on the top.\n");
	set_soft_amount(200);
	set_alco_amount(20);
	add_prop(HEAP_I_UNIT_VOLUME, 100);
	add_prop(HEAP_I_UNIT_VALUE, 100);
}
