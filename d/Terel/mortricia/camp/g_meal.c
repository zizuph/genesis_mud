inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("meal");
    set_short("gypsy meal");
    set_adj("gypsy");
    set_long(break_string(
	 "A complete gypsy meal. It consists of goulash, a red-beat " +
	 "salad, a pirogue, and finally, a cream layered cake. " +
	 "Yum-yum!\n"
    , 70));
    set_amount(100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
}
