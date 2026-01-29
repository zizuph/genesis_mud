inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include <stdproperties.h>
void
create_armour()

{
  set_name("helm");
  set_short("guardian helm");
  set_long(break_string(
           "This helmet is made of steel and are painted in red and black "+
           "colours. In the forehead, the sign of the cirathian guardian force "+
           "is placed.\n",60));
  set_adj("guardian");
  add_adj("cirathian");

  set_ac(18);
  set_am(({ 0, 0, 0}));
  set_at(A_HEAD);

  add_prop(OBJ_I_WEIGHT,3000);
  add_prop(OBJ_I_VOLUME,1500);
}
