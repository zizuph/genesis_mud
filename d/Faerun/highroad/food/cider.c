/* 
 * Apple Cider for an inn
 * Finwe, January 2002
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>

inherit "/std/drink";

void
create_drink()
{
    set_name("cider");
    set_short("apple cider");
    set_pname("apple ciders");
    set_pshort("apple ciders");
    set_long("This is a glass of fresh apple cider. It was pressed from apples and is golden colored. The cider has a slight fruity fragrance.\n");
    set_soft_amount(60);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
