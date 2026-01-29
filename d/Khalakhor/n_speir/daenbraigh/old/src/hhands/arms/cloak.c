/*
 * HH guards - cloak
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

  set_name("cloak");
  set_pname("cloaks");
  
  set_adj("rough");
  set_adj("woolen");
  
  set_short("rough woolen cloak");
  set_pshort("woolen cloaks");
  
  set_long("This cloak serves the guards of the Hammerhands guild. "+
	   "It is rough and made of thick wool, and looks to be quite "+
	   "warm and protective. It has a crossed-clubs symbol on the "+
	   "collar.\n");
  
  set_ac(HH_ACLASS/2);
  set_at(A_ROBE);
  set_am(({-1,-1,0}));
  
  add_prop(OBJ_I_WEIGHT, 2400);
  add_prop(OBJ_I_VOLUME, 1800);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(HH_ACLASS/2));
  add_prop(HH_PROPERTY,1);

}
