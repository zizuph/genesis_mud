inherit "/std/receptacle";
#include <stdproperties.h>


create_receptacle(){

set_name("coffin");
set_adj("stone");
set_long("It is an ancient stone coffin, the figure of a knight is carved on top of it.\n");

   add_prop(CONT_I_MAX_VOLUME, 999999);
   add_prop(CONT_I_MAX_WEIGHT, 999999);
add_prop(OBJ_M_NO_GET, 1);
  set_no_show_composite(1);
   add_prop(CONT_I_TRANSP, 0);


}

