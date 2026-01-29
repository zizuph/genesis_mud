/* A large dowel meant to be a leftover
 * from mechanical creatures
 * MAR 2008, Aeg
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("dowel");
    add_name("part");
    set_pname("dowels");
    set_adj( ({"thick", "wooden"}) );
    set_long("This is a cylindrical rod of wood that appears to "
        + "be 3 centemeters in diameter and a meter in length. "
        + "It looks quite sturdy.\n");
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 40);
}
