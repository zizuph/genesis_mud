inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("coat");
    set_short("polished chainmail coat");
    add_adj(({"polished", "chainmail"}));
    set_ac(32);
    set_am( ({-2,5,-2}) );
    set_at(A_BODY);
    set_long("This coat of padded chainmail covers the entire body. It has long sleeves " +
        "and nearly goes down to ankle length. It is belted at the waist for a better fit.\n");
    add_prop(OBJ_I_WEIGHT, 2200); 
    add_prop(OBJ_I_VOLUME, 950);
}
