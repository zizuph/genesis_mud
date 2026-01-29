/* This obj is cloned by /d/Emerald/caverns/npc/chef.c 
*/
inherit "/std/armour.c";
#include "defs.h"

inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
   set_name("apron");
   set_short("dirty apron");
   add_adj("dirty");
   set_long(
      "This is a terribly dirty apron.  There are "+
      "food stains of every kind everywhere you look.\n");
   set_ac(5);
   set_am( ({-2, 1, 1}) );
   set_at(A_ROBE);
}

string
query_recover()
{
   return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
   init_arm_recover(arg);
}
