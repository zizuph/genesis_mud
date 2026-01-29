 /* Derryn's helmet.
 code (c) 1998 Damian Horton */

#pragma strict_types
#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include "defs.h"
#include "/sys/formulas.h"

void create_armour()
{
  set_name("helmet");
  add_name("helm");
  set_short("tembo-skull helmet");
  set_long("This tembo skull has been carved so that it fits nicely on "+
	   "ones head, and can therefor serve as a helmet. The skull is "+
	   "discolored with age, and is marked from battles fought by its "+
	   "previous owner. Worn as a helmet, it does give one a somewhat "+
	   "frightening countenance.\n");
  set_adj("tembo-skull");
  set_adj("tembo");
  set_adj("skull");

  set_ac(28);
  set_am(({3,-1,-2}));
  set_at(A_HEAD);

  add_prop(OBJ_I_WEIGHT, 2600);
  add_prop(OBJ_I_VOLUME, 1350);
  add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(28)/3)+random(75)); 
}
