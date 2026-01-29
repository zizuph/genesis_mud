/*
* Palmer December 2002
 */

inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Shire/sys/defs.h"

void
create_food()
{
    ::create_food();

    set_name(({"cube", "sugar", "sugarcube", "sugar cube"}));
    set_pname("sugar cubes");
    set_adj("white");
    set_short("sugar cube");
    set_pshort("sugar cubes");
    set_long("Its a cube of sugar.\n");
    set_amount(20);
    add_prop(OBJ_I_VALUE, 1200);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 400);
}

init()
{
    ::init();
}
