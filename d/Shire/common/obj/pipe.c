inherit "/std/container";
#include "/d/Shire/common/defs.h"

create_object()
{

   set_short("shiny new wooden");
   add_adj(({"shiny","new","wooden"}));
   set_long("This shiny wooden pipe can be smoked if you will "+
   "put some herb in it, and you can chew on it as well.\n");

   add_prop(OBJ_I_WEIGHT, 109);
   add_prop(OBJ_I_VOLUME, 175);
   add_prop(CONT_I_WEIGHT, 500);
   add_prop(CONT_I_VOLUME, 500);
   add_prop(OBJ_I_VALUE, 50);
   add_prop(CONT_I_RIGID, 1);

}
