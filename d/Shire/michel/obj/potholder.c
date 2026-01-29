inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include "/sys/wa_types.h"


create_armour()
{
set_name("potholder");
     add_name("panholder");
     add_adj(({"dirty","stained"}));
     set_long("This looks like it would keep you from getting your hands burnt.\n");
     set_at(A_HANDS);
      set_ac(5);
     set_am(({-1,0,1}));
     add_prop(OBJ_I_WEIGHT, 100);
     add_prop(OBJ_I_VOLUME, 200);
     add_prop(OBJ_I_VALUE, random(64));

}
