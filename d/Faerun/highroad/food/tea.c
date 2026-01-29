/* 
 * Tea for an Inn
 * Finwe, November 2007
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>

inherit "/std/drink";

void
create_drink()
{
    set_name("tea");
    set_short("black tea");
    set_pname("black teas");
    set_pshort("black teas");
    set_long("This is a steamimg cup of black tea. It's made " +
        "of fermented leaves and has a black color. The tea " +
        "has a dark fragrance.\n");
    set_soft_amount(100);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
