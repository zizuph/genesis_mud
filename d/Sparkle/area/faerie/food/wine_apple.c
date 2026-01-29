/* Apple wine for Green Oaks
 * Finwe, March 2005
 */

inherit "/std/drink";
#include <stdproperties.h>

#define WINE    "apple"

void
create_drink()
{
        set_name("wine");
        add_name(WINE);
        add_name(WINE + " wine");
        set_pname("wines");
        add_pname(WINE + " wines");
        set_short("glass of " + WINE + " wine");
        set_pshort("glasses of " + WINE + " wine");
        set_long("This is a glass of " + WINE + " wine. It was distilled from wild apples. The wine has a clear color and a crisp, tart fragrance.\n");
        set_soft_amount(80);
        set_alco_amount(20);

	add_prop(OBJ_I_WEIGHT, 150);
	add_prop(OBJ_I_VOLUME, 150);
}
