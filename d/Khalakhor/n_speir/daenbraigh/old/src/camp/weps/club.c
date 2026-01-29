/*
 * Goblin garrison - regular chainmail
 * TAPAKAH, 04/2005
 */
#pragma strict_types

inherit "/d/Khalakhor/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>       
#include "../../camp/camp.h"

void
create_khalakhor_weapon()
{   
  set_name("club");
  set_pname("clubs");
  
  set_adj("rough");
  set_adj("iron");
  
  set_short("rough iron club");
  set_pshort("iron clubs");
  
  set_long("This club serves the regular troops of the goblin garrison\n"+
	   "It is rough, with a tempered iron head on wooden handle, and\n"+
	   "looks to be quite an efficient weapon.\n");
  
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);
  set_hit(WCLASS + random(6) - 3);
  set_pen(WCLASS + random(6) - 3);
  set_hands(W_ANYH);
    
  add_prop(OBJ_I_WEIGHT, 3200);
  add_prop(OBJ_I_VOLUME, 900);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WCLASS,WCLASS));
  add_prop(GG_PROPERTY,1);
}
