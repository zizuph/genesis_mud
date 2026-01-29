 /* Derryn's robe.
 code (c) 1998 Damian Horton
 Updated for Raumdor, March 2001 */

#pragma strict_types
#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include "/d/Cirath/defs.h"
#include <stdproperties.h>
#include <formulas.h>

void create_armour()
{
  set_name("robe");
  add_name("cloak");
  set_short("worn fur robe");
  set_long("This robe, fashioned from the fur of some animal, is hooded "+
	   "so as to provide welcome protection from the searing sun. "+
	   "It has obviously seen a lot of wear. It reeks of sweat and "+
	   "is stained beyond all cleaning.\n");
  set_adj("worn");
  add_adj("fur");

  set_ac(3);
  set_am(({0,0,0}));  
  set_at(A_ROBE);

  add_prop(OBJ_I_WEIGHT, 1900);
  add_prop(OBJ_I_VOLUME, 5500);
  add_prop(OBJ_I_VALUE, 5 + random(30));
}






