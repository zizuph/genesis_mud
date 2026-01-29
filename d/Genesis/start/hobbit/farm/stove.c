/*
 *  Stove inside the kitchen of the farm.
 */

#pragma save_binary

inherit "/std/container";

#include "defs.h"
#include "/sys/stdproperties.h"

create_container() {
   set_short("kitchen stove");
   set_pshort("kitchen stoves");
   set_name("stove");
   set_pname("stoves");
   set_adj("kitchen");
   set_long(break_string(
      "The kitchen stove smells like apple pies. It is an old kitchen "
    + "stove that needs wood to be inserted under it, in order to "
    + "heat it. The iron stove is still a bit warm.\n",70));

 /* Some properties of this stove */
   add_prop(OBJ_I_NO_GET, 1);             /* Not gettable       */
   add_prop(CONT_I_VOLUME, 7000);         /* 7.0 Ltr            */
   add_prop(CONT_I_MAX_VOLUME, 13000);    /* 6.0 Ltr inside     */
   add_prop(CONT_I_WEIGHT, 5000);         /* 5.0 Kg             */
   add_prop(CONT_I_MAX_WEIGHT,  8000);    /* 3.0 Kg inside      */
   add_prop(CONT_I_RIGID, 1);             /* The stove is rigid */

   if(!present("pie"))
      clone_object(STAND_DIR + "pie")->move(this_object());

   enable_reset();
}

reset_container() {
   if(!present("pie"))
      clone_object(STAND_DIR + "pie")->move(this_object());
}