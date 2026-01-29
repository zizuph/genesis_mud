/*********************************************************************
 * - tea.c                                                       - *
 * - This is a cup of tea to be used in SaMorgan Inn             - *
 * - Created by Damaris 08/2006                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
	set_name("tea");
	add_name(({"cup", "hot tea"}));
	set_adj(({"cup", "hot"}));
	set_short("cup of hot tea");
	set_pshort("cups of hot tea");
	set_long("This is a cup of hot tea. It is a perfect blend "+
	"of tea leaves that have been brewed with a delecate hint of "+
	"mint.\n");
	set_soft_amount(200);
	add_prop(HEAP_I_UNIT_VOLUME, 100);
	add_prop(HEAP_I_UNIT_VALUE, 100);
}
