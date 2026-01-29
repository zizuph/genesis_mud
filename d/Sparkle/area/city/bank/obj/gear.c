
/* A gear meant to be a leftover
 * from mechanical creatures
 * MAR 2008, Aeg
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("gear");
    add_name("part");
    set_pname("gears");
    set_adj("fine-toothed");
    set_adj("small");
    set_long("This gear is a small disk of metal with fine teeth "
        + "etched into the side.\n");
    add_prop(OBJ_I_VALUE, 115);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 40);
}
