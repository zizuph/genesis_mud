inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("chain");
    set_short("greaves");
    add_adj(({"chain", "greaves", "metal"}));
    set_ac(30);
    set_am( ({-2,5,-2}) );
    set_at(A_LEGS);
    set_long("These light chain greaves provide some protection for your legs. " +
        "The links are old and battered, but the piece of armour is still well " +
        "made and sturdy.\n");
    add_prop(OBJ_I_WEIGHT, 800); 
    add_prop(OBJ_I_VOLUME, 300);
}
