/*
 * Farmer's dress
 * -- Finwe, November 2006
 */

inherit "/std/armour";

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()

{
    set_name("dress");
    add_adj("plain");
    add_adj("cotton");
    set_short("plain cotton dress");
    set_long("This is a plain cotton dress. It has short sleaves and a long skirt that goes down to the knees..\n");

    set_ac(10);
    set_at(A_BODY);
    set_am(({0,0,0,}));
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);
}
