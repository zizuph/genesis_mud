inherit "/std/armour";

#include "/sys/wa_types.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"

create_armour()
{
  set_name("gloves");
  set_adj("guardian");
  add_adj("cirathian");
  set_short("pair of guardian gloves");
  set_pshort("pairs of guardian gloves");
  set_long("The gloves are made of red and black leather, the colours of "+
    "the cirathian guardian force.\n");

  set_default_armour(4, A_HANDS, ({0,0,0}), 0);

  add_prop(OBJ_I_WEIGHT,300);
  add_prop(OBJ_I_VOLUME,200);
}
