#pragma strict_types
inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

public void
create_armour()
{
    set_name("helm");
    set_short("blackened helm");
    set_long("An ancient steel helm, blackened by some unknown force.\n");
    set_adj(({"black","blackened"}));
    set_ac(25);
    set_am(({0,0,0}));
    set_at(A_HEAD);
    add_prop(OBJ_I_VOLUME, 300);
}
