/* Circlet for Sateela, by Gwyneth, 06/16/99 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("circlet");
    set_adj("flower");
    set_short("circlet of flowers");
    set_pshort("circlets of flowers");
    set_long("This is a purely decorative circlet of wild flowers twined " + 
        "together. Each flower, you notice, is beautiful, yet deadly.\n");
    set_ac(1);
    set_at(A_HEAD);
    add_prop(OBJ_I_VOLUME, 20);
}

