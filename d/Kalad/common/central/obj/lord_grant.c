/* a note that can be found in the city council. */
/* made by korat */

inherit "/std/scroll";
#include <stdproperties.h>
#include "/d/Kalad/defs.h"

void
create_scroll()
{
   set_name("sheet");
   set_adj("handwritten");
   set_long("A small piece of paper with some text written down on it.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 10);
   add_prop(OBJ_I_VOLUME, 20);
   add_prop("korat_lord_note",1);
    set_file("/d/Kalad/common/central/obj/lord_grant");
}

