inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("tray");
   set_adj("serving");
   set_long("This appears to be a basic serving tray carried by "
	+"one of the butlers in the Minthor House.  It has the "
	+"house symbol of the Minthor's on it, which is a drop "
	+"of water falling onto a desert of coins.  You could "
	+"probably bludgeon someone with this, just not really "
	+"well.\n");
   set_hit(15);
   set_pen(15);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
}
