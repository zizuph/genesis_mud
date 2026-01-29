/*
 * HH backpack
 * TAPAKAH, 10/2005
 */

#include <stdproperties.h>

#include "../../hhands/hhands.h"

inherit "/d/Genesis/std/pack";
inherit "/lib/keep"; 

void
create_pack()
{
  set_name("backpack");
  add_adj("leather");
  add_name(({"backpack",HH_OBJID + "_pack"}));
  set_long("A leather pack which can be worn on the back. "+
	   "There is a symbol of two crossed clubs above a forge "+
	   "sewn on it.\n");
	   
  set_mass_storage(1); 
  
  set_keep(1); 
  
  add_prop(CONT_I_WEIGHT, 4500);
  add_prop(CONT_I_MAX_WEIGHT, 150000);
  add_prop(CONT_I_VOLUME, 8000);
  add_prop(CONT_I_MAX_VOLUME, 150000);
  
  add_prop(OBJ_I_VALUE, 450);
}
