/* Furnitures for the third floor for the castle.
 * Coded by Shiva (12/15/98)
 * Used by Marisol (12/17/98)
*/

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("sheet");
    set_adj(({ "dusty", "dirty-white" }));
    set_long("A dusty, dirty-white sheet. It is covering a piece of "+
        "furniture in the room.\n");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 2);
}                          