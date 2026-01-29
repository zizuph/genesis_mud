#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>
#include <filter_funs.h>

inherit "/std/weapon";

public void
create_weapon()
{
  set_name("axe");
  set_short("tarnished handaxe");
  set_long("A traditional looking handaxe, it has quite a few notches in "+
	   "the obviously well worn blade. It is of quite good quality, and "+
	   "is still quite affective.\n");
  set_adj("brutal");
  set_default_weapon(30, 30, W_AXE, W_SLASH, W_ANYH);
  add_prop(OBJ_I_VALUE, 1050);
  add_prop(OBJ_I_WEIGHT, 7500);
  add_prop(OBJ_I_VOLUME, 4000);
}




