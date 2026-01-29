inherit "/std/object";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>


create_object()
{

   int clean, fueled, lit, extinguished;
     set_short("old rusty stove");
     set_name("stove");
     add_adj(({"old","rusty"}));
     set_long("This old stove hardly looks like it will heat anything. "+
      "You doubt it has seen much attention lately, and needs "+
      "some work.\n");

     add_prop(OBJ_I_WEIGHT, 10000); /* Not too heavy to carry */
     add_prop(OBJ_I_VOLUME, 100000000); /* Pretty darn big */

     clean = 0;
     fueled = 0;
     lit = 0;
     extinguished = 0;
}
