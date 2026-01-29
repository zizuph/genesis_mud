inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("shield");
    set_short("polished metal shield");
    add_adj(({"polished", "metal"}));
    set_ac(20);
    set_am( ({2,2,2}) );
    set_at(A_SHIELD);
    set_long("This polished round steel shield, is somewhat heavy. It covers about half " +
        "of your torso for sufficient protection from attacks. It bears the symbol " +
        "of Telberin in it's center.\n");
    add_prop(OBJ_I_WEIGHT, 300); 
    add_prop(OBJ_I_VOLUME, 450);
}
