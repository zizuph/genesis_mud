inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
   set_name("claw");
   add_name("_sealion_claw");
   set_adj("sealion");
   add_adj("lion");
   add_adj("sea");
   set_short("sea lion claw");
   set_long("This is an undamaged claw from the rare and incredibly " +
       "dangerous sea lion. These claws are in high demand by " +
       "game hunters and collectors, and fetch an excellent price " +
       "from merchants.\n");
   add_prop(OBJ_I_VOLUME, 50);
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VALUE, 2000);
}

/*
 * Function name: query_recover
 * Description  : We allow this standard object to recover.
 * Returns      : string - the recovery string.
 */
public string
query_recover()
{
    return MASTER;
}