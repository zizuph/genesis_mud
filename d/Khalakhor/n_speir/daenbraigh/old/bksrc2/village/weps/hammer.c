/*
 * Smith's hammer - Goblin village.
 * TAPAKAH, 09/2005
 */
inherit "/d/Khalakhor/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       
#include "../../village/village.h"
#include "../../nspeir.h"

void
create_khalakhor_weapon()
{   
  set_name("hammer");
  set_pname("hammers");
  
  set_adj("heavy");
  add_adj("iron");
  
  set_short("heavy iron hammer");
  set_pshort("heavy iron hammers");
  
  set_long(BSN("A very heavy iron hammer with a beak. It is very balanced "+
	       "and probably serves good its owner - the smith."));
  
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hit(VCCLASS + random(18) - 3);
  set_pen(VCCLASS + random(6) - 3);
  set_hands(W_ANYH);
    
  add_prop(OBJ_I_WEIGHT, 12000);
  add_prop(OBJ_I_VOLUME, 3000);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(),query_pen()));
}
