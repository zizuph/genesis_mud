inherit "/std/armour";
#include <stdproperties.h>
#include "/sys/wa_types.h"
#include "/sys/macros.h"

void
create_armour()

{
  set_name("shield");
  set_short("guardian shield");
  set_long("This shield is made of red and black painted steel "+
    "with the symbol of the cirathian guardian force in the middle of it.\n");
  set_adj("guardian");
  add_adj("cirathian");

  set_ac(25);
  set_am(({ 0, 1, 1 }));
  set_at(A_SHIELD);

  add_prop(OBJ_I_WEIGHT,3000);
  add_prop(OBJ_I_VOLUME,1500);
}
