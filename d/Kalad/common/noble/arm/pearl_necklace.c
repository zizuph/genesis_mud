/*     Created by:      Sarr
 *     Location:        
 *     Modified:        Toby, 970919 (fixed typos and plural)
 */

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"


void
create_armour()
{
    ::create_armour();
    set_name("necklace");
    set_adj("pearl");
    set_short("pearl necklace");
    set_pshort("pearl necklaces");
    set_long("Many beautiful shiny pearls line this necklace. It is "+
    "so fabulous that you are mesmerized for a bit at the sparkling "+
    "lights reflected of the surfaces of the pearls.\n");
    set_ac(0);
    set_at(A_NECK);
    add_prop(OBJ_I_WEIGHT,70);
    add_prop(OBJ_I_VOLUME,10);
    add_prop(OBJ_I_VALUE,550+random(30));
}

