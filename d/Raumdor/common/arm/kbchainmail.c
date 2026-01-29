inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* war-torn black chainmail, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("chainmail");
    set_adj("war-torn");
    add_adj("black");
    set_short("war-torn black chainmail");
    set_long("This dirty, filth covered chainmail looks well-worn and "+
    "used. It is covered with dents and tears. It looks like it was just "+
    "used in a battle. Etched on the chest is an emblem in the shape of "+
    "a grim skull.\n");
    set_ac(30);
    set_at(A_BODY);
    set_am(({-1,2,0}));
    add_prop(OBJ_I_WEIGHT,9000);
    add_prop(OBJ_I_VOLUME,7200);
    add_prop(OBJ_I_VALUE,100);
}
