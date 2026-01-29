/*
    The crystal is placed in the meditation room of the Smiths Guild
    so that meditating people have something to look at :)
*/

#pragma save_binary;

inherit "/std/object";

#include "smiths.h"
#include "stdproperties.h"
#include "/d/Shire/common/defs.h"

void
create_object() {
   set_name("crystal");
   set_adj("blue");
   set_adj("round");
   set_long("It is rumoured that this large round crystal is of elven make."+
      " It is said that when a person stares intently into the crystal it is"+
      " possible to enter a sort of trance where one can estimate one's"+
      " powers.\n");

   add_prop(OBJ_I_NO_GET,1);

   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,500);
}
