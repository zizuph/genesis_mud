/* 
   Stole the file from /d/Gondor/pelargir/obj/stew.c
   at Apr. 29. 1995 - Regards, Boromir
*/

/*
 *   f_cake.c:  Food for the Hobbiton bakery.
 */

inherit "/std/food";

#include <stdproperties.h>

void
create_food() 
{
    set_name("ham");
    add_name("plate");
    set_adj("fat");
    set_short("plate with some nice fat ham");
    set_pshort("plates with some nice fat ham");
    set_long(break_string(
	"The ham looks really delicious (for those who love "+
	"fat food).\n",70));
    add_prop(OBJ_I_VALUE, 0);
    set_amount(100);
    add_prop(OBJ_I_WEIGHT,120);
    add_prop(OBJ_I_VOLUME,96);
}
