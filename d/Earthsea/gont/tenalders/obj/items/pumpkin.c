/*  The scarecrow's head
*  coded by Amelia   5/24/97
*/

inherit "/std/food.c";

#include <stdproperties.h>
#include <macros.h>

void
create_food()
{
    set_name("pumpkin");
    set_adj(({"large", "orange"}));
    set_short("large orange pumpkin");
    set_long(break_string("A large orange pumpkin. You "+
	"notice it has a funny face drawn on one side of it.\n",70));
    set_amount(350);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 20);
}
