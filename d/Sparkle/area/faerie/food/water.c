/* Glass of water for Green Oaks
 * Finwe, March 2005
 */

inherit "/std/drink";
#include <stdproperties.h>

void
create_drink()
{
        set_name("water");
        set_pname("waters");
        set_short("glass of water");
        set_pshort("glasses of water");
        set_adj(({"glass of", "glass"}));
        set_long("This is a glass of fresh water. It is crystal clear " +
            "and looks refreshing.\n");
        set_soft_amount(60);

	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VOLUME, 100);
}
