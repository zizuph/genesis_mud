/* A metal nail meant to be a leftover
 * from mechanical creatures
 * MAR 2008, Aeg
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("nail");
    add_name("part");
    set_pname("nails");
    set_adj( ({ "small", "metallic"}) );
    set_long("This nail appears to be 2 centemeters in length and looks "
        + "very standardized. The metal nail is void of rust and not "
        + "bent.\n");
    add_prop(OBJ_I_VALUE, 20);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
} /* create_object() */