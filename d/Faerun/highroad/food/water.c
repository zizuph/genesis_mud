/* 
 * Water for an inn 
 * Finwe, November 2007
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>

inherit "/std/drink";

void
create_drink()
{
    set_name("water");
    set_pname("waters");
    set_short("glass of water");
    set_pshort("glasses of water");
    set_adj(({"glass of", "glass"}));
    set_long("A refreshing glass of clear mountain water.\n");
    set_soft_amount(60);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

}
