/* 
 * Wine for an Inn
 * Finwe, November 2007
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>

inherit "/std/drink";

void
create_drink()
{
    set_name("wine");
    add_name("glass");
    set_pname("wines");
    add_pname("glasses");
    set_short("glass of white wine");
    set_pshort("glasses of white wine");
    set_long("This is a glass of white wine. It is made from berries that have been fermented. The wine is a light yellow color and has a fruity bouquet.\n");
    set_soft_amount(90);
    set_alco_amount(25);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

}
