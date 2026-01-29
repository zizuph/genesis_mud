/*
 * Guard's spear - one-handed polearm.
 * Tapakah, 04/2021
 */

#include "../defs.h"
inherit SM_WEAPON;

void
create_weapon ()
{
  set_name("spear");
  set_pname("spears");

  set_adj("short");
  set_adj("steel-tipped");

  set_short("short steel-tipped spear");
  set_long("This spear is pretty short - about a yard long, but it has a nasty "+
	   "looking steel tip, which seems to be able to both stab and cut.\n");
           
}
