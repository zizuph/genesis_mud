#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

create_object()
{
  set_name("bones");
  add_name("knucklebones");
  set_adj("dirty");
  add_name("cubes");
  add_name("blocks");
  add_adj(({"white","knuckle"}));
  set_short("set of dirty white cubes");
  set_long("This is a small set of dirty white cubes that have "+
    "some strange patterns scratched into the sides.  The corners "+
    "are all rounded off, and the cubes are pretty banged up.\n");
  add_prop(OBJ_I_VOLUME,150);
  add_prop(OBJ_I_WEIGHT,250);
  add_prop(OBJ_I_VALUE,50); 
}