/*********************************************************************
 * - mocha.c                                                       - *
 * - This is a cup of mocha to be used in SaMorgan Inn             - *
 * - Created by Damaris 08/2006                                    - *
 *********************************************************************/
#pragma strict_types
inherit "/std/drink";
#include <stdproperties.h>

public void
create_drink()
{
	set_name("mocha");
	add_name(({"cup", "hot mocha"}));
	set_adj(({"cup", "hot"}));
	set_short("cup of hot mocha");
	set_pshort("cups of hot mocha");
	set_long("This is a cup of hot mocha. It is a perfect blend "+
	"of imported coffee beans that have been ground and brewed "+
	"with a delecate hint of spices and chocolate and with sweet "+
	"cream added.\n");
	set_soft_amount(200);
	add_prop(HEAP_I_UNIT_VOLUME, 100);
	add_prop(HEAP_I_UNIT_VALUE, 100);
}
