
inherit "/std/receptacle";
#include <stdproperties.h>
#include "defs.h"

int i;

void
create_container()
{
   set_name("bag");
   set_adj("small");
   set_adj("draw-string");
   set_short("small draw-string bag");
   set_long("It is just a small leather bag with a drawstring.\n");
   
   add_prop(CONT_I_WEIGHT, 500);
   add_prop(CONT_I_MAX_WEIGHT, 3000);
   add_prop(CONT_I_MAX_VOLUME, 10000);
   add_prop(CONT_I_VOLUME, 1000);
   for(i=0; i<20; i++)
   {
      object diamond;
      seteuid(getuid());
      diamond=clone_object(PIRATES_DIR+"obj/diamond");
      diamond->move(this_object());
   }
   add_prop(CONT_I_CLOSED, 1);
   
}
