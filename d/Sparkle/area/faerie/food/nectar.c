/* Glass of Nectar for Green Oaks
 * Finwe, March 2005
 */

inherit "/std/drink";
#include <stdproperties.h>

void
create_drink()
{
        set_name("nectar");
        set_pname("nectars");
        set_short("glass of nectar");
        set_pshort("glasses of nectars");
        set_adj(({"glass of", "glass"}));
        set_long("This is a glass of nectar. It is made from fresh water" +
            "and flowers. It has a sweet fragrance and looks refreshing.\n");
        set_soft_amount(60);

	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VOLUME, 100);
}
