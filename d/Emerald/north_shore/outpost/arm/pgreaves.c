inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("plate");
    set_short("polished steel greaves");
    add_adj(({"polished", "greaves"}));
    set_ac(36);
    set_am( ({3,3,3}) );
    set_at(A_LEGS);
    set_long("These polished greaves will protect your legs quite well. " +
        "Engraved upon the knee joint is the sigil of Telberin.\n");
    add_prop(OBJ_I_WEIGHT, 2800); 
    add_prop(OBJ_I_VOLUME, 750);
}
