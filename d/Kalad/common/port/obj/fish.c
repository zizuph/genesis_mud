inherit "/std/food";
#include <stdproperties.h>
/* by antharanos */
create_food()
{
    set_name("fish");
    set_adj("big");
    add_adj("fat");
    set_long("The biggest, fattest, juiciest fish you have ever laid "+
      "eyes upon.\n");
    set_amount(1000);
    add_prop(OBJ_I_WEIGHT,1000);
    add_prop(OBJ_I_VOLUME,600);
}
