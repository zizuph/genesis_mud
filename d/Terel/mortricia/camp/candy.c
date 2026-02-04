inherit "/std/food";
#include <stdproperties.h>

create_food()
{
    set_name("candy");
    set_adj("sweet");
    set_short("handful of sweet candy");
    set_pshort("handfuls of sweet candy");
    set_long(break_string(
	"It's sweet candy. It's newly made and smells wonderful.\n",
	70));
    set_amount(11);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_I_VALUE, 10);
}
