
/*
 * Ceremonial Alb
 * No value
 * Only used for ceremonies
 *
 */
 
inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>

void create_armour() {
    set_name(({"white robe","robe"}));
    add_name("_ceremonial_robe");
    set_adj("white");
    set_short("white robe");
    set_long("It is a white robe used for ceremonial purposes.\n");
    set_ac(1);
    set_at(A_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_M_NO_SELL,1);
}
