/* a litter_bin for trash or what not. */
/* created for Icewall by Stevenson */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>

inherit "/std/container";

void create_container() {
   set_short("litter bin");
   set_name("bin");
   add_name("trash");
   set_adj("litter");
   set_long("This is a litter bin. It is a great place for discarding "
      + "worthless bits of rubbish.\n");
   
   add_prop(CONT_I_VOLUME,100);
   add_prop(CONT_I_WEIGHT,100);
   add_prop(CONT_I_MAX_VOLUME,200);
   add_prop(CONT_I_MAX_WEIGHT,200);
   add_prop(CONT_I_RIGID,1);
   add_prop(OBJ_M_NO_GET,"Why would you want to do that?\n");
}
