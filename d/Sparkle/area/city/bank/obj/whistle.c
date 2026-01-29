
/* A whistle meant to be a leftover
 * from mechanical creatures
 * MAR 2008, Aeg
 */
 
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("whistle");
    add_name("part");
    set_pname("whistles");
    set_adj("steam");
    set_adj("oversized");
    set_long("This whistle must have been attached to a steam engine "
        + "of some sort. It appears that only heated air will have it "
        + "make noise.\n");
    add_prop(OBJ_I_VALUE, 115);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 40);
}
