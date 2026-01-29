/* modified by Teth, Dec 6 1996 */
#include <macros.h>
inherit "/std/drink";

public void
create_drink()
{
    set_soft_amount(125);
    set_alco_amount(10);
    set_name("beer");
    add_name("alcohol");
    set_adj(({"crisp","refreshing"}));
    set_pname("beers");
    add_pname("alcohols");
    set_short("crisp refreshing beer");
    set_pshort("crisp refreshing beers");
    set_long("This is a crisp refreshing beer, brewed using malt " +
        "and hops. It is golden in colour, as a beer should be.\n");
    set_drink_msg("Ahhh...it certainly is refreshing!\n");
    add_prop(OBJ_I_WEIGHT, 125);
    add_prop(OBJ_I_VOLUME, 125);
}

