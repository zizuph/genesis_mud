inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_armour()
{
  set_name("ring");
  add_name("Troll_Quest_Ring");
  set_adj("ebony");
  set_adj("little");
  set_short("little ebony ring");
  set_pshort("small ebony rings");
  set_long("This is a small ring carved out of ebony. It has an inscription on the\n"+
    "inside: Leydon, son of Beleg.\n");
  set_at(A_ANY_FINGER);
  set_ac(0);
  add_prop(OBJ_I_WEIGHT,20);
  add_prop(OBJ_I_VOLUME,10);
  add_prop(OBJ_I_VALUE,60);
}
