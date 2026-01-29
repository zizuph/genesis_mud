inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* dirty black platemail, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("platemail");
    set_adj("dirty");
    add_adj("black");
    set_short("dirty black platemail");
    set_long("A rather filthy piece of armour, this platemail nevertheless "+
    "looks usable. It seems to be made of blackened steel. Among the dents "+
    "you see etched, a grim looking skull.\n");
    set_ac(35);
    set_at(A_BODY);
    set_am(({-1,2,0}));
    add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VOLUME,8600);
    add_prop(OBJ_I_VALUE,120);
}
