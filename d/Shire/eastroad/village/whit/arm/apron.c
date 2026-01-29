inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include "/d/Shire/defs.h"
 
create_armour()
{
   set_name("apron");
   set_pname("aprons");
   set_short("white apron");
   set_adj(({"white","dusty"}));
   set_long("A simple white apron covered with flour.\n");
  set_ac(5);
  set_at( A_BODY );
  add_prop(OBJ_I_WEIGHT, 200);
  add_prop(OBJ_I_VOLUME, 100);
  add_prop(OBJ_I_VALUE, 40);
}
