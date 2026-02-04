/*
  
  by Udana, /2006
*/

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Terel/include/Terel.h"
#define AT A_ANY_FINGER
#define AC 1

inherit SILVER_DIR + "armour/colour_armour";

create_armour()
{
  set_name("ring");
  set_adj("golden");
  set_short("golden ring with @@query_colour@@ jewel");
  set_pshort("golden rings with @@query_colour@@ jewel");
  set_long("A thin ring made of pure gold with single @@query_colour@@ jewel.\n");
  /* (impale, slash, bludgeon) */
  set_default_armour(AC, AT, ({0, 0, 0}));
  
  add_prop(OBJ_I_VALUE, 10000);
  add_prop(OBJ_I_WEIGHT, 15);
  add_prop(OBJ_I_VOLUME, 10);
}
