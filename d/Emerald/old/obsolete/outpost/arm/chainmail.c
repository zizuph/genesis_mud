inherit "std/armour.c";

#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name("coat");
    set_short("sturdy chainmail coat");
    set_pshort("sturdy chainmail coats");
    set_pname("sturdy chainmail coats");
    add_pname("armours");
    set_adj("sturdy");
    add_adj("chainmail");

    set_ac(32);
    set_am( ({-2,5,-2}) );
    set_at(A_BODY);
    set_long("This coat of padded chainmail seems well made and " +
        "covers your upper torso. Numerous steel links provide " +
        "good protection for your chest and back.\n");
    add_prop(OBJ_I_WEIGHT, 2200); 
    add_prop(OBJ_I_VOLUME, 950);
}
