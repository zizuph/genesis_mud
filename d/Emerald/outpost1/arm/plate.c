inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("plate");
    set_short("polished steel breastplate");
    add_adj(({"polished", "breastplate"}));
    set_ac(40);
    set_am( ({3,3,3}) );
    set_at(A_TORSO);
    set_long("This highly polished steel breastplate looks very protective. " +
        "Engraved upon the breastplate, flowing designs surround the sigil of " +
        "Telberin.\n");
    add_prop(OBJ_I_WEIGHT, 2800); 
    add_prop(OBJ_I_VOLUME, 750);
}
