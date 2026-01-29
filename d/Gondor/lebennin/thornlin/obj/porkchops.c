/*  I (Boromir) stole this file from:    */

/*
 *  Steak.c  - food for the Rangers Inn.
 */

/*
 * Redid the file for Thornlin inn
*/

inherit "/std/food";
#include <stdproperties.h>

void
create_food() 
{
    set_name("pork chops");
    add_name("chops");
    add_name("plate");
    set_adj("plate");
    set_short("plate of pork chops");
    set_pshort("plates of pork chops");
    set_long(break_string(
	"The plate of pork chops seems delicious.\n",70));
    add_prop(OBJ_I_VALUE, 0);
    set_amount(200);
    add_prop(OBJ_I_WEIGHT,175);
    add_prop(OBJ_I_VOLUME,200);
}
