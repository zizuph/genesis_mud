inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

void
create_drink()
{
   set_alco_amount(10);
   set_name(({"coke","bottle"}));
    add_name("diet coke");
   set_short("diet coke");
   set_pshort("cokes");
   set_adj("cold");
   set_long("It's an ice cold diet coke in an old fashioned bottle.\n");
      add_prop(OBJ_I_WEIGHT, 1790);
      add_prop(OBJ_I_VOLUME, 1860);
}
