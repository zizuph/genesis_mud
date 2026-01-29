inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_armour()
{
  set_name("ring");
  set_adj("gold");
  set_adj("little");
  set_short("small gold ring");
  set_pshort("small gold rings");
  set_long("This is a small ring made of gold. It looks old.\n");
  set_at(A_ANY_FINGER);
  set_ac(1);
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VOLUME,10);
  add_prop(OBJ_I_VALUE,1440);
}
