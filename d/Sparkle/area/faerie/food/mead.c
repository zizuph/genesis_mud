/* Glass of Mead for Green Oaks
 * Finwe, March 2005
 */

inherit "/std/drink";
#include <stdproperties.h>

void
create_drink()
{
        set_name("mead");
        set_pname("mead");
        set_short("fresh golden mead");
        set_pshort("fresh golden meads");
        set_adj(({"fresh", "golden"}));
        set_long("This is a pint of fresh mead. It was brewed from fresh " +
            "honey and water, and has a golden color to it. The mead " +
            "looks cool and refreshing.\n");
        set_soft_amount(50);
        set_alco_amount(10);

	add_prop(OBJ_I_WEIGHT, 100);
	add_prop(OBJ_I_VOLUME, 100);
}
