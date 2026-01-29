inherit "/std/food";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

create_food()
{
    set_name("orange");
    set_pname("oranges");
    set_short("delicious orange");
    set_long("This is some fresh orange from Shire. It has "+
     	     "an orange color, and looks quite delicious.\n");
     	     
    set_amount(150);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
    
}
 