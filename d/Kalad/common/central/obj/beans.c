/*
 * Some beans for a coffee quest
 *
 * To be ground by the grinder
 *
 * Korat    Additions by Napture
 *
 */
 
inherit "/std/food";

#include "/d/Kalad/defs.h"
#include <stdproperties.h>

void
create_food()
{
   set_name("beans");
   set_adj("handful");
   add_adj("of");
   set_short("handful of coffee beans");
     /* You don't need a set_short() here, this would automatically be
      * generated from the name and adj...
      */
   set_long("It's a handful of coffee beans that wafts into your "+
     "nose a wonderful aroma.\n");
   set_amount(100);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,150);
   add_prop(OBJ_I_VALUE,50);

   add_prop("_korat_quest_beans", 1);
}


