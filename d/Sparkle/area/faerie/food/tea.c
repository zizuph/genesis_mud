/* Glass of tea for Green Oaks
 * Finwe, March 2005
 */

inherit "/std/drink";
#include <stdproperties.h>

void
create_drink()
{
        set_name("tea");
        set_pname("fruit tea");
        set_short("glass of fruit tea");
        set_pshort("glasses of fruit tea");
        set_adj(({"glass of", "glass"}));
        set_long("This is a glass of fruit tea. It is bright colored and " +
            "refreshing looking.\n");
        set_soft_amount(100);

	add_prop(OBJ_I_WEIGHT, 150);
	add_prop(OBJ_I_VOLUME, 150);
}
