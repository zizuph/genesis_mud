inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("helm");
    set_short("light iron");
    add_adj(({"light", "iron"}));
    set_ac(30);
    set_at(A_HEAD);
    set_long("This light iron helm is not very heavy, but it does " +
        "provide some protection for the head and neck. The sigil " +
        "of Telberin is engraved upon the neck guard.\n");
    add_prop(OBJ_I_WEIGHT, 200); 
    add_prop(OBJ_I_VOLUME, 250);
}
