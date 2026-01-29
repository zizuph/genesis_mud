/*
 * HH guards - shield
 * TAPAKAH, 04/2005
 */
#pragma strict_types

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>     
#include <macros.h>

#include "../../hhands/hhands.h"

inherit "/d/Khalakhor/std/armour";

void
create_khalakhor_armour()
{   
  if(! IS_CLONE)
    return;

  ::create_khalakhor_armour();
  set_name("shield");
  set_pname("shields");
  
  set_adj("polished");
  set_adj("iron");
  
  set_short("polished iron shield");
  set_pshort("iron shields");
  
  set_long("This shield serves the guards of the Hammerhands guild. "+
	   "It is polished and made of tempered iron, and looks to be quite "+
	   "a protective armour. It has a crossed-clubs symbol on outer "+
	   "side.\n");
  
  set_ac(HH_ACLASS);
  set_at(A_SHIELD);
  set_am(({-1,-1,2}));
  
  add_prop(OBJ_I_WEIGHT, 3900);
  add_prop(OBJ_I_VOLUME, 1400);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(HH_ACLASS));
  add_prop(HH_PROPERTY,1);

}
