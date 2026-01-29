/* Stralle @ Genesis 041220
 */
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("pouch");
    set_pname("pouches");
    set_adj(({"small", "leather"}));
    set_short("small leather pouch");
    set_pshort("small leather pouches");
    set_long("It is a small leather pouch kept closed by a leather " +
             "string sown into its opening. Inside lies a fine grained " +
             "glimmering powder.\n");

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 0);
}
