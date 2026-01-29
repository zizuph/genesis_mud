
inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>
 
void create_armour() 
{
    set_name("robe");
    set_adj(({"long","black"}));
    set_short("long black robe");
    set_long("It is a long black robe that flows almost to the ground.\n");
    set_ac(5);
    set_at(TS_ROBE);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME,  800);
}
