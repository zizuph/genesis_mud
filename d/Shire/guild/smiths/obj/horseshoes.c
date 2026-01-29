inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "smiths.h"

#define ITEM_TYPE "misc"


void
create_object() {

   set_name("set of horseshoes");
   add_name(({"horseshoes", "set"}));
   set_pname("sets of horseshoes");

   set_long("These horseshoes are made of iron and appear to be in good condition.\n");

   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,300);
}

string
query_smiths_item() {
   return ITEM_TYPE;
}

