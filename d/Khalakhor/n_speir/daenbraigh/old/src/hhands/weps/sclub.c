/*
 * HH superior club
 * TAPAKAH, 10/2005
 */
#pragma strict_types

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       

#include "../../hhands/hhands.h";

inherit "/d/Khalakhor/std/weapon";

void
create_khalakhor_weapon()
{   
  set_name("club");
  set_pname("clubs");
  
  set_adj("balanced");
  set_adj("iron");
  
  set_short("balanced iron club");
  set_pshort("iron clubs");
  
  set_long("This club is the weapon of choice of the elite Hammerhands. "+
	   "It's head is wrought of iron and made even heavier with lead, "+
	   "and the handle looks to be made of iron too, but is wrapped in "+
	   "leather. Two crossed clubs are engraved on the handle. The club "+
	   "is wonderfully balanced.");

  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hit(HH_WCLASS + random(6) + 3);
  set_pen(HH_WCLASS + random(6) + 3);
  set_hands(W_ANYH);
    
  add_prop(OBJ_I_WEIGHT, 3200);
  add_prop(OBJ_I_VOLUME, 1100);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HH_WCLASS,HH_WCLASS));
  add_prop(HH_PROPERTY,1);
}
