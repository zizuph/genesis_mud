inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>


void
create_armour()
{
    set_name("mantle");
    set_ac(15);
    set_at(A_BODY | A_ARMS | A_LEGS | A_LEGS);
    set_am( ({ 4, 4, -10 }) );
    set_adj("black");
    add_adj("crimson-hooded");
    set_short("black crimson-hooded mantle");
    set_pshort("black crimson-hooded mantle");
    set_long("This is a black mantle. Made "+
             "from wool that has been dyed black, it"+
             "has a crimson red hood, that protects the "+
             "head and covers the face. It has a small "+
             "sign of a red fist on the back.\n"); 
    add_prop(OBJ_I_VOLUME, 3050);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
}

