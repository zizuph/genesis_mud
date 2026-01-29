/* 
 * Beer for Faerun
 * Finwe, November 2007
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>

inherit "/std/drink";

void
create_drink()
{
    set_name("beer");
    set_pname("beers");
    set_short("dark beer");
    set_pshort("dark beers");
    set_adj(({"dark", "cold"}));
    set_long("This is a dark cold beer. It is made from fermenting grains and flavorings. It looks refreshing and delicious.\n");
    set_soft_amount(100);
    set_alco_amount(6);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);       
}
