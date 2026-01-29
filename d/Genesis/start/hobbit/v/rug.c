/*
 *  Rug that lies in the mayor's house.
 */

#pragma save_binary

inherit "/std/object";

#include "defs.h"
#include "/sys/stdproperties.h"

create_object() {
   set_short("handwoven rug");
   set_pshort("handwoven rugs");
   set_name("rug");
   set_pname("rugs");
   set_adj("handwoven");
   set_long(break_string(
      "This handwoven rug was a gift for the mayor of Hobbiton "
    + "from Bilbo Baggins. He brought it back from one of his many "
    + "journeys to countries far away. The rug feels soft like the "
    + "finest silk, even though it has been made of wool.\n",70));

 /* Some properties of this rug */
   add_prop(OBJ_I_WEIGHT, 3500);    /* 3.5 Kg            */
   add_prop(OBJ_I_VALUE, 40);       /* 40 Copper coins   */
   add_prop(OBJ_I_VOLUME, 3000);    /* 3.0 Ltr           */
   add_prop(MAGIC_I_RES_FIRE, 1);   /* Fire resistant    */
   add_prop(OBJ_S_WIZINFO, "Magical handwoven rug, fire-resistant.\n");
}
