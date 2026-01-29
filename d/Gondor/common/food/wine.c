inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink()
{
   set_name("wine");
   add_name("bottle");
   set_pname(({"wines", "bottles", }));
   set_adj("white");
   set_short("bottle of white wine");
   set_pshort("bottles of white wine");
   set_long(
      "The sparkling white wine comes from the ripe grapes that "
    + "were harvested in the land of Ithilien some years ago.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(200);
   set_alco_amount(24);
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 200);
}
