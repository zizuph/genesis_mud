inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("pants");
   set_pname("pants");
   set_adj("padded");
   add_adj("black");
   set_short("black padded pants");
   set_long("This pair of pants appears to be made from some "
   	+"sort of tanned hide.  After tanning it appears to have "
   	+"been dyed black and affixed with pads to better protect "
   	+"the wearer.\n");
   set_ac(30);
   set_at(A_LEGS);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,1000);
}

