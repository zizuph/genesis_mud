/* made by Korat 16.02 1995 */
inherit  "/std/container";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>



void
create_container()
{
   set_name("cabinet");
   set_adj("wooden");
   set_long("Its a large wooden cabinet with a door occupying "+
      "most of the front side of it.\n");
   add_prop(CONT_I_WEIGHT, 40000);
   add_prop(CONT_I_MAX_WEIGHT, 100000);
   add_prop(CONT_I_VOLUME, 10000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(OBJ_I_VALUE, 200);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(CONT_I_TRANSP, 0);
   add_prop(CONT_I_RIGID,1);
}