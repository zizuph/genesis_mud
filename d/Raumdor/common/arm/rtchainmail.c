inherit "/std/armour";
#include "/d/Raumdor/defs.h"
/* tarnished silver chainmail, by Sarr */

void
create_armour()
{
    ::create_armour();
    set_name("chainmail");
    set_adj("tarnished");
    add_adj("silver");
    set_short("tarnished silver chainmail");
    set_long("This dirty, tarnished chainmail looks like its been "+
    "through a war. Its dented, and marred, but still usable. On the "+
    "chest piece, you see a golden sun with rays engraved.\n");
    set_ac(30);
    set_at(A_BODY);
    set_am(({-1,2,0}));
    add_prop(OBJ_I_WEIGHT,9000);
    add_prop(OBJ_I_VOLUME,7200);
    add_prop(OBJ_I_VALUE,100);
}
