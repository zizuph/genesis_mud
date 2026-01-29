/*
 * Goblin garrison - regular chainmail
 * TAPAKAH, 04/2005
 */
inherit "/d/Khalakhor/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       
#include "../../village/village.h"

void
create_khalakhor_weapon()
{   
  set_name("knife");
  set_pname("knifes");
  
  set_adj("sharp");
  add_adj("iron");
  
  set_short("sharp iron knife");
  set_pshort("iron knives");
  
  set_long("A sharp knife, carefully wrought from iron. This knife looks more like\n"+
	   "home utensil than a weapon.\n");
  
  set_wt(W_KNIFE);
  set_dt(W_SLASH);
  set_hit(VWCLASS + random(6) - 3);
  set_pen(VWCLASS + random(6) - 3);
  set_hands(W_ANYH);
    
  add_prop(OBJ_I_WEIGHT, 900);
  add_prop(OBJ_I_VOLUME, 300);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(VWCLASS,VWCLASS));
}
