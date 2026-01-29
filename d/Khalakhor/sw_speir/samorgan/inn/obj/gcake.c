/*********************************************************************
 * - gcake.c                                                       - *
 * - This is a ginger ginger cake to be used in SaMorgan Inn       - *
 * - Created by Damaris 08/2006                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
	set_name("cake");
	set_adj(({"sweet", "golden", "butter"}));
	set_short("piece of golden butter cake");
	set_pshort("pieces of golden butter cake");
	set_long("This is a piece of golden butter cake. It has a "+
	"sweet sweet cream butter and dripping icing along the sides. "+
	"It is warm, moist and compliments a meal perfectly.\n");
	set_amount(50);
	add_prop(HEAP_I_UNIT_VOLUME, 30);
	add_prop(HEAP_I_UNIT_VALUE, 50);
}
