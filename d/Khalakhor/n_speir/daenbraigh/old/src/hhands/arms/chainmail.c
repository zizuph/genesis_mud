/*
 * HH guards - chainmail
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
  
  set_name("chainmail");
  set_pname("chainmails");

  set_adj("polished");
  set_adj("iron");
  
  set_short("polished iron chainmail");
  set_pshort("iron chainmails");
  
  set_long("This chainmail serves the guards of the Hammerhands guild. "+
	   "It is polished and made of tempered iron, and looks to be quite "+
	   "a protective armour. It has a crossed-clubs symbol on the breast"+
	   ".\n");
  
  set_ac(HH_ACLASS);
  set_at(A_BODY);
  set_am(({-1,-1,2}));
  
  add_prop(OBJ_I_WEIGHT, 6400);
  add_prop(OBJ_I_VOLUME, 2500);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(HH_ACLASS));
  add_prop(HH_PROPERTY,1);
}
