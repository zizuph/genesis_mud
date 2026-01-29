
/* A joint meant to be a leftover
 * from mechanical creatures
 * MAR 2008, Aeg
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("joint");
    add_name("part");
    set_pname("joints");
    set_adj("hinged");
    set_adj("standardized");
    set_long("This joint seems to have been created to connect two stable "
        + "parts and allow them a certain range of motion.\n");
    add_prop(OBJ_I_VALUE, 115);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 40);
}
