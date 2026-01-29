inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("breastplate");
    set_short("polished steel breastplate");
    set_pshort("polished steel breastplates");
    set_pname("breastplates");
    add_pname("armours");
    set_adj("polished");
    add_adj("steel");

    set_ac(40);
    set_am( ({3,3,3}) );
    set_at(A_TORSO);
    set_long("This highly polished steel breastplate looks very protective. " +
        "Engraved upon the breastplate, flowing designs surround the sigil of " +
        "Telberin.\n");
    add_prop(OBJ_I_WEIGHT, 4000); 
    add_prop(OBJ_I_VOLUME, 2500);
}
