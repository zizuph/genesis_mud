inherit "/std/receptacle";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>


create_receptacle()
{

   int clean, fueled, lit, extinguished;
     set_short("old rusty stove");
     set_name("stove");
     add_adj(({"old","rusty"}));
     set_long("This old iron stove hardly looks like it will heat anything. "+
      "You doubt it has seen much attention lately, and needs "+
      "some work.\n");

     add_prop(CONT_I_WEIGHT, 10000); /* Not too heavy to carry */
     add_prop(CONT_I_MAX_WEIGHT, 100000); /* Let us put things in it */
     add_prop(CONT_I_VOLUME, 100000000); /* Pretty darn big */
     add_prop(CONT_I_MAX_VOLUME, 10000000000); /* Put things in it */
     add_prop(CONT_I_RIGID, 1); /* Stoves are rigid */
     add_prop(CONT_I_CLOSED, 1); /* Start with it closed */

     clean = 0;
     fueled = 0;
     lit = 0;
     extinguished = 0;
}
