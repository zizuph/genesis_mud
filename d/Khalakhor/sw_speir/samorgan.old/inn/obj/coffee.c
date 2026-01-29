/*********************************************************************
 * - coffee.c                                                      - *
 * - This is a cup of coffee to be used in SaMorgan Inn            - *
 * - Created by Damaris 08/2006                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
	set_name("coffee");
	add_name(({"cup", "hot coffee"}));
	set_adj(({"cup", "hot"}));
	set_short("cup of hot coffee");
	set_pshort("cups of hot coffee");
	set_long("This is a cup of hot coffee. It is a perfect blend "+
	"of imported coffee beans that have been ground and brewed "+
	"with a delecate hint of nutmeg.\n");
	set_soft_amount(200);
	add_prop(HEAP_I_UNIT_VOLUME, 100);
	add_prop(HEAP_I_UNIT_VALUE, 100);
}
