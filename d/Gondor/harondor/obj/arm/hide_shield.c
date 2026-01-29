/* 
 * Standard Haradrim shield from Harondor.
 * Serif, July 2001.
 */

inherit "/std/armour";
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
  set_name("shield");
  set_pname("shields");
  set_short("black hide shield");
  set_pshort("black hide shields");
  set_adj("black");
  set_adj("hide");
  set_adj("round");
  set_long("This black shield is made from tough hide stretched over a "
      + "wooden frame. It is light but sturdy, and the hide seems as "
      + "though it might provide some good protection for a traveling "
      + "warrior.\n");
  set_default_armour(30,A_SHIELD,({ -1, 1, 2}),0);
  add_prop(OBJ_I_WEIGHT, 2300);
  add_prop(OBJ_I_VOLUME, 900);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(15)-7);
}
