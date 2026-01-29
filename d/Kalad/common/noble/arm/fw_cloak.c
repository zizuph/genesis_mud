/*     Created by:      Sarr
 *     Location:        
 *     Modified:        Toby, 970919 (fixed typos)
 */

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"


void
create_armour()
{
    ::create_armour();
    set_name("cloak");
    set_adj("fine");
    add_adj("woven");
    set_short("fine woven cloak");
    set_long("This a very fine cloak made of cotton and silk. Along "+
    "the back, you see the emblem of the High Lord of Kabal.\n");
    set_ac(2);
    set_at(A_ROBE);
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,280);
}

