/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
// modified by Lilith Mar 2022: removed mystic guild references.

inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
   set_short("aquamarine leaf");
   set_pshort("aquamarine leaves");
   set_name("leaf");
   set_adj("aquamarine");
   add_adj(({"shevoral", "thick","crisp", "serrated"}));
//   add_name("mystic_quest_leaf");
   set_long("A beautiful aquamarine leaf from the sacred shevoral bush.\n"+
       "It is thick and crisp, with serrated edges.\n");
   add_item(({"edge", "edges", "leaf edge"}),
       "The edges of the aquamarine leaf are serrated.\n");
   add_prop(OBJ_I_VALUE, 100);
}

