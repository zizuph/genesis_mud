/* A toothless comb, totally useless
 * by Teth, Feb15,96
*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
   set_name("comb");
   set_adj("toothless");
   add_adj("ivory");
   set_short("toothless comb");
   set_pshort("toothless combs");
   set_long("This toothless comb is apparently the loot from some poor " +
            "victim of a goblin raid. It must have once been a family " + 
            "heirloom, but it is now only a cracked piece of ivory.\n");
   
   add_prop(OBJ_I_VALUE, 50);
   add_prop(OBJ_I_WEIGHT,50);
   add_prop(OBJ_I_VOLUME,123);
}
