/*********************************************************************
 * - rdragon.c                                                     - *
 * - Roasted meat for SaMorgan Inn.                                - *
 * - Created by Damaris@Genesis 08/2006                            - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
	set_name("dragon");
	add_name("meat");
	add_name("fillet");
	set_adj(({"spiced", "red"}));
	set_short("slice of spiced red dragon fillet");
	set_pshort("slices of spiced red dragon fillet");
	set_long("This is a slice of spiced red dragon fillet. It is "+
	"a speciality of the prized cook at SaMorgan Inn. The "+
	"spices used makes the meat tender and juicy.\n");
	set_amount(80);
	add_prop(HEAP_I_UNIT_VOLUME, 80);
	add_prop(HEAP_I_UNIT_VALUE, 180);
}
