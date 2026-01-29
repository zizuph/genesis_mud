
/* A wheel meant to be a leftover
 * from mechanical creatures
 * MAR 2008, Aeg
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("wheel");
    add_name("part");
    set_pname("wheels");
    set_adj( ({ "small", "complex"}) );
    set_long("This is a small wheel that seems to have been connected "
        + "to a machine of some sort. It has attachments to the top "
        + "that are very complex.\n");
    add_prop(OBJ_I_VALUE, 115);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 40);
}
