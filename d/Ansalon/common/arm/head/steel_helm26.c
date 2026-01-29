/* Ashlar, 4 Oct 97 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("helm");
    set_adj("steel");
    set_ac(26);
    set_at(A_HEAD); 
    set_short("steel helm");    set_long("This is a steel helm. It is flared at the neck and has a " +
        "cruel spike set on top of it.\n");
    add_prop(OBJ_I_VOLUME, 1000);
}

