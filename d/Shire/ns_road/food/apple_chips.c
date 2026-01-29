/*
 * Food for North/South road Farm
 * Finwe, Feruary 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
inherit "/std/food";

void
create_food()
{
    set_name("chips");
    set_adj("apple");
    set_long("This is a handful of apple chips. They are large slices " +
        "of apples that have been dried in the sun. The chips are " +
        "seasoned with cinnamon and dusted with sugar.\n");
    set_amount(70); 
    add_prop(OBJ_I_WEIGHT, 100); 
    add_prop(OBJ_I_VOLUME, 100);
}
