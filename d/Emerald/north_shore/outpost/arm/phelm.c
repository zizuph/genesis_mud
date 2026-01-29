inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("helm");
    set_short("polished steel helm");
    add_adj(({"polished", "steel"}));
    set_ac(36);
    set_at(A_HEAD);
    set_long("This polished steel helm is quite heavy, but it does " +
        "provide good protection for the head and neck. The sigil " +
        "of Telberin is engraved upon the neck guard.\n");
    add_prop(OBJ_I_WEIGHT, 450); 
    add_prop(OBJ_I_VOLUME, 300);
}
