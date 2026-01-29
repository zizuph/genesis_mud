inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("chain");
    set_short("chain bracers");
    add_adj(({"chain", "bracers"}));
    set_ac(30);
    set_am( ({-2,5,-2}) );
    set_at(A_ARMS);
    set_long("This set of light chain bracers will provide some protection " +
        "for your arms. You can see the remnants of past battles in the " +
        "gashes and nicks in the chain links, but all of them seem to be " +
        "well attached to the armour.\n");
    add_prop(OBJ_I_WEIGHT, 500); 
    add_prop(OBJ_I_VOLUME, 350);
}
