inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("bracers");
    set_short("polished steel bracers");
    set_pshort("sets of polished steel bracers");
    set_pname("sets of polished steel bracers");
    add_pname("armours");
    set_adj("polished");
    add_adj("steel");
    add_adj("set of");

    set_ac(36);
    set_am( ({3,3,3}) );
    set_at(A_ARMS);
    set_long("This polished set of bracers will protect your arms quite well. " +
        "Engraved upon the elbow joints is the sigil of Telberin.\n");
    add_prop(OBJ_I_WEIGHT, 1800); 
    add_prop(OBJ_I_VOLUME, 900);
}
