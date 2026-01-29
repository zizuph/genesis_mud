/* Ashlar, 15 Jul 97 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("boots");
    set_pname("boots");
    set_adj("soft");
    add_adj("leather");
    set_short("soft leather boots");
    set_pshort("soft leather boots");
    set_ac(3);
    set_at(A_FEET);
    set_long("The soft leather boots are pretty comfortable for walking " +
        "in, but they do not offer much protection against blows.\n");
    add_prop(OBJ_I_VOLUME, 900);
    set_am(({0,0,0}));
}
