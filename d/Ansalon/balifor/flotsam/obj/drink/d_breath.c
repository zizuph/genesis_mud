inherit "/std/drink";
#include <stdproperties.h>

create_drink()
{
   set_soft_amount(300);
   set_alco_amount(45);
   set_name("breath");
   add_name("mug");
   add_name("breath");
   set_pname("breaths");
   add_pname("mugs");
   set_adj("dragon");
   set_short("mug of Dragon Breath");
   set_pshort("mugs of Dragon Breath");
   set_long("This black, potent-smelling brew is a favourite " +
      "amongst the draconians of Flotsam. By the looks of it, this drink " +
      "has to be thrown " +
      "down quickly, as it seems to be eating away at the mug! \n");
   add_prop(OBJ_I_WEIGHT, 200);
   add_prop(OBJ_I_VOLUME, 200);
}
