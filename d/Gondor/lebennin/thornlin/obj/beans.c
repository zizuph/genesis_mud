/*
 * Using this file for Thornlin Inn from the date Apr. 29. 1995
 * Regards, Boromir
 */
inherit "/std/food";

#include <stdproperties.h>

void
create_food() 
{
    set_name("bacon");
    add_name("plate");
    add_name("beans");
    set_adj("hot");
    set_short("hot plate of beans and bacon");
    set_pshort("hot plates of beans and bacon");
    set_long(break_string(
	"The hot plate of beans and bacon smells so delicious that you "+
	"feel like eating it right away.\n",70));
    add_prop(OBJ_I_VALUE, 0);
    set_amount(150);
    add_prop(OBJ_I_WEIGHT,160);
    add_prop(OBJ_I_VOLUME,105);
}
