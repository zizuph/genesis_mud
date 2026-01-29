inherit "/std/container";

#include <macros.h>
#include "/sys/stdproperties.h";
#include "/d/Gondor/defs.h"

create_container() {
   set_name("chest");
   set_short("battered chest");
   set_pshort("battered chests");
   set_adj("battered");
    add_adj(({"old","wooden"}));
    set_long(BSN("This old wooden chest has a battered lid which can " +
	"barely move. "+
        "The wooden slats that form the chest are slightly rotted also, but "+
        "it still is capable of holding quite a bit."));
   add_prop(CONT_I_WEIGHT,     4000);   /* It weighs 4 Kg            */
   add_prop(CONT_I_MAX_WEIGHT, 25000);   /* It can contain up to 21 Kg  */
   add_prop(CONT_I_VOLUME,     8000);   /* It measures 8 Ltr         */
   add_prop(CONT_I_MAX_VOLUME, 31000);   /* It can contain 23 Ltr       */
   add_prop(CONT_I_RIGID, 0);            /* It is not a rigid object   */
   add_prop(CONT_I_REDUCE_VOLUME,150);
   add_prop(CONT_I_REDUCE_WEIGHT,150);
   add_prop(OBJ_I_VALUE,90);    /* Value ?? cc*/
   add_prop(OBJ_M_NO_SELL,"@@no_sell");
}

query_recover() { return MASTER + ":"; }

mixed
no_sell()
{
  if(sizeof(all_inventory(TO)))
    return BSN("Luckily you notice that the chest is not empty just " +
      "before you sell it. Perhaps you should remove everything from " +
      "the chest before you sell it? ");
  return 0;
}
