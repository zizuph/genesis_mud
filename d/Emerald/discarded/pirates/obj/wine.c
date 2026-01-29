/* This obj is cloned by /d/Emerald/pirates/npc/fisherman.c
 */

inherit "/std/drink";
#include <stdproperties.h>
#include "defs.h"

create_drink()
{
   set_name("wine");
   set_adj("strong");
   set_long("This wine smells so potent, you think twice about "+
      "drinking it.\n");
   set_soft_amount(700);
   set_alco_amount(40);
   add_prop(OBJ_I_WEIGHT, 700);
   add_prop(OBJ_I_VOLUME, 700);
   add_prop(OBJ_M_NO_DROP,"The fisherman would be "+
      "crushed if you just left his father's wine laying around "+
      "for anyone to take.\n");
}
