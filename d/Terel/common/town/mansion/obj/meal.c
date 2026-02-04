inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("meal");
    set_short("plate with delicious meal");
    set_pshort("plates with delecious meal");
    set_adj("delicious");
    set_long(break_string(
	 "A complete delicious meal. It consists of goulash, a red-beat " +
	 "salad, a pirogue, and finally, a cream layered cake. " +
	 "Yum-yum!\n"
    , 70));
    set_amount(100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
}
