inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Shire/defs.h"
 
create_armour()
{
  set_name("tunic");
  set_pname("tunics");
  set_short("leather tunic");
  set_adj(({ "leather", "hobbit" }));
  set_long("A simple leather tunic made for a hobbit.\n");
  set_ac(5);
  set_at( A_BODY );
  add_prop(OBJ_I_WEIGHT, 200);
  add_prop(OBJ_I_VOLUME, 100);
  add_prop(OBJ_I_VALUE, 40);
}
