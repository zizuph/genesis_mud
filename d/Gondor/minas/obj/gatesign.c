inherit "/std/scroll";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"

create_scroll()
{
  set_name("sign");
  set_adj("large");
  add_adj("wooden");
  set_long("The sign stands next to the junction of the roads coming\n"+
    "from north, northeast, south and west. Letters have been carved\n"+
    "into its wooden surface, and painted in black.\n"+
    "You can probably read it.\n");
  set_file(MINAS_DIR+"obj/gatesign.txt");
  add_prop(OBJ_M_NO_GET,"The large sign is too heavy, in addition to being\n"+
    "stuck in the ground.\n");
}
