/* chapel/arm/tux.c is cloned by chapel/npc/usher.c */
inherit "/std/armour";
 
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
 
void
create_armour()
{
    set_name("tuxedo");
    set_short("white tuxedo");
    set_long("This is a white tuxedo, impeccably "+
       "tailored to hide the glint of shining chainmail underneath."+
       "\n");
 
    add_item(({"chainmail"}), "Upon closer examination "+
       "the chainmail and tuxedo seemed to be connected in some "+
       "fashion.  Maybe merged magically.\n");
 
    set_adj("white");
 
    set_default_armour(25, A_BODY,  0,  0);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME,  680);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25) + random(100));
}
