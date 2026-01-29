inherit "/std/container";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_container() {
   set_name("box");
   add_name("charity box");
set_adj("charity");
   set_short("charity box");
   set_long(break_string(
      "The charity box is installed here to allow adventurers to show "
    + "their good side. In it, you can drop any items you want to give "
    + "away to charity. This way other, less wealthy adventurers may "
    + "benefit from their fellow adventurers.\n",70));

   add_prop(OBJ_I_NO_GET,1);
   add_prop(CONT_I_WEIGHT,      10000);
   add_prop(CONT_I_MAX_WEIGHT, 100000); 
   add_prop(CONT_I_VOLUME,       5000);
   add_prop(CONT_I_MAX_VOLUME,  20000);
}

