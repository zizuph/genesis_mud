/*********************************************************************
 * - pale.c                                                        - *
 * - This is a pint of ale to be used in SaMorgan Inn              - *
 * - Created by Damaris 12/2001                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
	set_name("ale");
	add_name(({"pint", "dark ale"}));
	set_adj(({"pint", "dark"}));
	set_short("pint of ale");
	set_pshort("pints of ale");
	set_long("This is a pint of very dark ale. It has been fermented "+
	"quite well and has a nice head of foam on the top.\n");
	
	set_soft_amount(400);
	set_alco_amount(40);
	add_prop(HEAP_I_UNIT_VOLUME, 100);
	add_prop(HEAP_I_UNIT_VALUE, 100);
}
