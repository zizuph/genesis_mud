inherit "/std/object";

#include <stdproperties.h>
#include "/d/Shire/smiths/smiths.h"

void
create_object() {

    set_name(({"bar","smith_bar","copper_smith_bar"}));
    set_adj("copper");
    set_short("copper bar");
    set_long("This copper bar is marked with the sign of the Smiths "+
        "Guild. It can be used for forging copper items.\n");

    add_prop(OBJ_I_WEIGHT, 7500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 50);
}
