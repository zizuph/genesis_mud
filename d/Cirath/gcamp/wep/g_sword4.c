inherit "/std/weapon";
#include "../defs.h"
#include "/d/Cirath/common/defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("sabre");
   add_name("sword");
   set_adj("curved");
   add_adj("iron");
   set_long("The blackened iron of this curved sword looks to be "
   	+"in amazingly good condition and well maintained.  The "
   	+"edge on it is razor sharp, easily capable of splitting "
   	+"a man in two with one swing.  Its curved blade is "
   	+"designed for slicing through things, and you can almost "
   	+"feel the sabre urging you to test it out.\n");
   set_hit(37);
   set_pen(37);
   set_wt(W_SWORD);
   set_dt(W_SLASH);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,1500);
}

