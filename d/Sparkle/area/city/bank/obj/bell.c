
/* A bell meant to be a leftover
 * from mechanical creatures
 * MAR 2008, Aeg
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("bell");
    add_name("part");
    set_pname("bells");
    set_adj("metallic");
    set_adj("small");
    set_long("This bell seems to have been attached to something "
        + "much larger than itself. It seems to have not been "
        + "created to stand alone.\n");
    add_prop(OBJ_I_VALUE, 115);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 40);
}
