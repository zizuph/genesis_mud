/* a leaf */

inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("leaf");
    set_pname("leaves");
    set_short("evergreen leaf");
    set_pshort("evergreen leaves");
    set_adj("evergreen");
    set_long("A bright evergreen leaf.\n");
    set_amount(100); /* 50 grams of food. */
    add_prop(OBJ_I_WEIGHT, 10); 
    add_prop(OBJ_I_VOLUME, 10);
}
