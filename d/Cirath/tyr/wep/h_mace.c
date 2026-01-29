inherit "/std/weapon";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>
 
create_weapon()
{
   set_name("mace");
   set_adj("obsidian");
   add_adj("heavy");
   set_long("This mace has a handle made of strong agafari wood, "
	+"and a head made of a large black obsidian ball.  You think if "
	+"you hit someone in the head it will hurt pretty bad.\n");
   set_hit(27);
   set_pen(27);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_ANYH);

}

