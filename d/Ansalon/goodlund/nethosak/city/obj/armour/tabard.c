inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


void
create_armour()
{
    set_name("tabard");
    set_ac(1);
    set_at(A_ROBE);
    set_am( ({ 0, 0, 0 }) );
    set_adj("blue");
    add_adj("imperial");
    set_short("imperial blue tabard");
    set_pshort("imperial blue tabards");
    set_long("This is one of the imperial tabards found "+
             "only in the city of Nethosak, and worn by "+
             "the imperial guards there. This tabard has "+
             "a large sign of a clenched fist on the back. "+
             "The tabard has been dyed blue, and the "+
             "different layers of wool has been sewed "+
             "together, making it look like a very formal "+
             "piece of equipment.\n");

    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(1));
}

