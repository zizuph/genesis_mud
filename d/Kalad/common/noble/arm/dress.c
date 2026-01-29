inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* SARR */

void
create_armour()
{
    ::create_armour();
    set_name("dress");
    set_adj("fine");
    add_adj("woven");
    set_short("fine woven dress");
    set_long("This is a magnificant dress! It is pure snow white, with "+
    "many sparkling crystal studs on it. It is made of the finest fabric "+
    "and made from the best taylor in Kabal!\n");
    set_ac(2);
    set_at(A_BODY);
    add_prop(OBJ_I_WEIGHT,600);
    add_prop(OBJ_I_VOLUME,100);
    add_prop(OBJ_I_VALUE,300);
}

