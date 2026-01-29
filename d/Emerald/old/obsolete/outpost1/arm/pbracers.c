inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("plate");
    set_short("polished steel bracers");
    add_adj(({"polished", "bracers"}));
    set_ac(36);
    set_am( ({3,3,3}) );
    set_at(A_ARMS);
    set_long("This polished set of bracers will protect your arms quite well. " +
        "Engraved upon the elbow joints is the sigil of Telberin.\n");
    add_prop(OBJ_I_WEIGHT, 1200); 
    add_prop(OBJ_I_VOLUME, 400);
}
