/* Gully Dwarf Stew by Teth Jan 18 1997 */

inherit "/std/food";
#include "../local.h"

public void
create_food()
{
    set_name("stew");
    add_name("food");
    set_pname("stews");
    add_pname("foods");
    set_adj("gully");
    set_short("gully stew");
    set_pshort("gully stews");
    set_long("This is a gully stew, a concoction of unknown ingredients " +
        "loved by gully dwarves everywhere. If you eat this batch, you " +
        "best hope it doesn't poison you. Then again, that is true for " +
        "any batch of gully stew.\n");
    set_amount(5);
}
