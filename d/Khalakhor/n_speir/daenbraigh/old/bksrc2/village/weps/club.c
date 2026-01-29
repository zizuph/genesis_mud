/*
 * Barman's club - Goblin village.
 * TAPAKAH, 04/2005
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
  set_name("club");
  set_pname("clubs");
  
  set_adj("thick");
  add_adj("wooden");
  
  set_short("thick wooden club");
  set_pshort("thick clubs");
  
  set_long(BSN("A large, thick wooden club. It feels like a good thing to"+
	       "swing or smash at your enemies."));
  
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hit(VCCLASS + random(6) - 3);
  set_pen(VCCLASS + random(6) - 3);
  set_hands(W_ANYH);
    
  add_prop(OBJ_I_WEIGHT, 9000);
  add_prop(OBJ_I_VOLUME, 3000);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(query_hit(), query_pen()));
}
