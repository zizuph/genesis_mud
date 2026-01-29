#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/armour";

public void
create_armour()
{
  set_name("helm");
  set_short("blackened helm");
  set_long("An ancient steel helm, blackened by some unknown force.\n");
  set_adj(({"black","blackened"}));
  set_ac(25);
  set_am(({0,0,0}));
  set_at(A_HEAD);
  add_prop(OBJ_I_VALUE, 450);
  add_prop(OBJ_I_VOLUME, 300);
  add_prop(OBJ_I_WEIGHT,1000);
}




