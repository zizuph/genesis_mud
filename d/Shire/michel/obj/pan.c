inherit "/std/container";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"



create_container()
{

     set_name("sheet");
     add_name("pan");
     add_name("_shire_baking_pan_");
     add_adj(({"old","rugged"}));
     set_short("old rugged cooking sheet");
     set_pshort("old rugged cooking sheets");
     set_long("This piece of scrap metal is long and flat. "+
      "It looks as though it could withstand intense heat.\n");

     add_prop(CONT_I_WEIGHT, 3000);
     add_prop(CONT_I_MAX_WEIGHT, 6000);
     add_prop(CONT_I_VOLUME, 1700);
     add_prop(CONT_I_MAX_VOLUME, 10000);
     add_prop(OBJ_I_VALUE, 21);


}
