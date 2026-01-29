inherit "/std/armour";
#include "/sys/stdproperties.h"
#include <wa_types.h>
#include "defs.h"

void
create_armour()
{
   set_name("breastplate");
   set_adj("chitin");
   set_long("This is a breastplate made from the chitinous carapace "
	+"of a large insectoid creature. It seems to be very protective, "
	+"while also being lightweight and not too hot.\n"); 
   set_default_armour(25,A_BODY, 0, 0);
}





