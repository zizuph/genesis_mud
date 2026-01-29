inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


void
create_armour()
{
    set_name("robe");
    set_ac(22);
    set_at(A_ROBE);
    set_am( ({ 2, 1, 2 }) );
    set_adj("black");
    add_adj("silver-embroidered");
    set_short("silver-embroidered black robe");
    set_pshort("silver-embroidered black robes");
    set_long("This is a magnificent black robe. Made "+
             "from wool that has been dyed black, it"+
             "has some silver threads that have been "+
             "embroidered into the wool. It has a small "+
             "sign of a red fist on the back.\n"); 
    add_prop(OBJ_I_VOLUME, 2050);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
}

