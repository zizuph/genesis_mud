// file name:    dhamier.c
// creator(s):   Casca, 11/24/99
// revisions:    
// purpose:      
// note:         
// bug(s):       
// to-do:        


inherit "/std/weapon";

#include <wa_types.h>
#include "/sys/stdproperties.h"
#include "/d/Avenir/common/common.h"


create_weapon()
{

    set_name("dhamier");
    set_pname("dhamiers");
    add_pname("weapons");
    add_name(({"knife","dagger","weapon"}));
    add_adj(({"pierced","silver"}));
    set_short("pierced silver dhamier");
    set_pshort("pierced silver dhamiers");
    set_long("This dagger is a dhamier, the sacred dagger of the "+
        "sybarite people. This one is as exquisite example of an "+
        "already beautiful form of dagger. The characteristic "+
        "double curved, double edged blade has been forged from "+
        "steel with a pool-and-eye damascus finish. "+
        "The base of the blade has been pierced and sculpted into "+
        "the likeness of a humanoid shoulder with a feathered wing. "+
        "The hilt is carved from a single piece of clear crystal "+
        "and you can see the tang has also been carefully shaped "+
        "to resemble an arm with the hand sticking out of the "+
        "pommel and holding a silver globe. The wing in the "+
        "blade has been traced with silver to accentuate the "+
        "details.\n");


   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH);
   set_hit(15);
   set_pen(20);

   add_prop(OBJ_I_VOLUME,400);
   add_prop(OBJ_I_WEIGHT,870);
   add_prop(OBJ_I_VALUE,385);
}
