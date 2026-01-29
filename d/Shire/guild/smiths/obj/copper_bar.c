/*
 *  A copper bar created for use in
 *  events. Based on the iron bar.
 *     Toby, 2008-05-02
 *
 *  Modification log:
 *
 */

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Shire/guild/smiths/smiths.h"

void
create_object() {

   set_name("bar");
   add_name( ({"copper_smith_bar", "smiths_copper_bar"}) );
   set_adj("copper");
   set_short("copper bar");
   set_pshort("copper bars");

   set_long("This is a copper bar bearing the mark of the Shire smiths guild. "+
      "It is of the kind used for forging items.\n");

   add_prop(OBJ_I_WEIGHT,3500);
   add_prop(OBJ_I_VOLUME,2000);
   add_prop(OBJ_I_VALUE, 80);
}
