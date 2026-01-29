/*
 * A dirty bag
 *
 * Revision history:
 * /Mercade, 26 November 1993; changed from container to /std/receptacle.c
 */

inherit "/std/receptacle";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_container()
{
   set_name("bag");
   set_short("dirty bag");
   set_pshort("dirty bags");
   set_adj("dirty");
   set_long("This dirty bag looks like it has been buried somewhere.\n");
   add_prop(CONT_I_WEIGHT,     1000);    /* It weighs 1 Kg            */
   add_prop(CONT_I_MAX_WEIGHT, 16000);   /* It can contain up to 15 Kg  */
   add_prop(CONT_I_VOLUME,     3000);    /* It measures 3 Ltr         */
   add_prop(CONT_I_MAX_VOLUME, 23000);   /* It can contain 20 Ltr       */
   add_prop(CONT_I_RIGID, 0);            /* It is not a rigid object   */
   add_prop(CONT_I_CLOSED, 1);
   add_prop(CONT_I_REDUCE_VOLUME,150);
   add_prop(CONT_I_REDUCE_WEIGHT,150);
   add_prop(OBJ_I_VALUE,50);    /* Value 40 cc*/
   add_prop(OBJ_M_NO_SELL,"@@no_sell");
}

string
query_recover()
{
    return 0;
}

void
init_recover(string arg)
{
    init_container_recover(arg);
}

mixed
no_sell()
{
  if(sizeof(all_inventory(TO)))
    return BSN("Luckily you notice that the bag is not empty just " +
      "before you sell it. Perhaps you should remove everything from " +
      "the bag before you sell it?");
  return 0;
}
