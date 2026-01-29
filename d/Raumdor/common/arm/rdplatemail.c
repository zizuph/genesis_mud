inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* dented silver platemail, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("platemail");
    set_adj("dented");
    add_adj("silver");
    set_short("dented silver platemail");
    set_long("This dirty, and well-used platemail looks to be made of "+
    "some kind of silver steel. Although it is dented and marred in "+
    "many places, like it was just used in a major war, it is still "+
    "usable, and has some value. A symbol of a golden sun with rays "+
    "adorns the chest plate.\n");
    set_ac(35);
    set_at(A_BODY);
    set_am(({-1,2,0}));
    add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VOLUME,8600);
    add_prop(OBJ_I_VALUE,120);
}
