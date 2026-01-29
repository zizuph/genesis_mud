/* 
 * Chicken egg from the High Road Villiages
 * -- Finwe, August 2006
 */
 
inherit "/std/object";
#include "stdproperties.h"

create_object()
{
    set_name("egg");
    add_name("_chicken_egg");
    set_short("large chicken egg");
    set_pshort("large chicken eggs");
    set_adj(({"large", "chicken" }));
    set_long("This is a large chicken egg. It is smooth and a brownish color.\n");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop("faerun_chicken_egg", 1);

}
