/*
 * Mortis 9.2014
 *
 * Adventurer's Guild donation box.
 */

#include "../../local.h"
#include <stdproperties.h>

inherit "/std/container";

create_container() {
   set_name("chest");
   add_name("box");
   set_adj("donation");
   add_adj(({"wide", "open"}));

   set_short("wide open donation chest");
   set_long("This wide, oak chest is open for anyone to donate anything they "
   + "think might be useful to an adventurer just getting started in the "
   + "world. You should put money or equipment in it.\n");
   
    add_prop(CONT_I_MAX_WEIGHT,  250000);
    add_prop(CONT_I_MAX_VOLUME,  250000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "Don't you dare take the Adventurer's Guild "
    + "donation box. You're a horrible person.\n");
}