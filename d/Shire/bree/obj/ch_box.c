/*
 *   Charity box for Bree
 */

inherit "/std/container";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

create_container() {
   set_name("box");
   set_pname("boxes");
   set_adj("charity");
   set_short("charity box");
   set_pshort("charity boxes");
   set_long(
      "The charity box is installed here to allow adventurers to show "
    + "their good side. In it, you can drop any items you want to give "
    + "away to charity. This way other, less wealthy adventurers may "
    + "benefit from their fellow adventurers.\n");

   add_prop(OBJ_I_NO_GET,1);
   add_prop(CONT_I_WEIGHT,      10000);
   add_prop(CONT_I_MAX_WEIGHT, 100000);    /* Can contain 90 Kg */
   add_prop(CONT_I_VOLUME,       5000);
   add_prop(CONT_I_MAX_VOLUME,  20000);    /* Can contain 15 l  */
   add_prop(CONT_I_RIGID,1);
   add_prop(CONT_I_TRANSP, 1);

/*
   clone_object(STAND_DIR + "rnd_armour")->move(this_object());
*/
}

