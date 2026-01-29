
/*
 *   object:      the black pearl, for use in the mermaid quest
 *   coder(s):      12/8/95    by Amelia
 *   Modifications by Maniac 6/9/96 
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

#include SEA_QUESTS

void
create_object()
{
   set_name("pearl");
   add_name(MERMQ_PEARL_ID); 
   set_adj("black");
   set_short("black pearl");
   set_pshort("black pearls");
   set_long("This is a rare black pearl. Examining it closely, "+
        "you see that it is about the size of your thumbnail. "+
        "It glows with a dark and mysterious lustre. "+
        "It could be a gift for a queen.\n");

   add_prop(OBJ_I_VOLUME, 20);
   add_prop(OBJ_I_VALUE, 1000);
   add_prop(OBJ_I_WEIGHT, 20);
}

