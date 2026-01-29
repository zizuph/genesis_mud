
/*
 *   object:      stick
 *   coder(s):    14/7/16    by Jaacar
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

void
create_object()
{
   set_name("stick");
   set_adj("driftwood");
   set_short("driftwood stick");
   set_pshort("driftwood sticks");
   set_long("It is a small driftwood stick. It has likely "+
       "washed up to shore from the sea.\n");

   add_prop(OBJ_I_VOLUME, 20);
   add_prop(OBJ_I_VALUE,   0);
   add_prop(OBJ_I_WEIGHT, 20);
}

