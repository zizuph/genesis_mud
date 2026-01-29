inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

#define SHIRE_SHIP_QUEST "_shire_ship_quest"

create_object()
{
  set_name("bauble");
  set_short("glittering bauble");
  set_adj("glittering");
  set_long("This "+short()+" is really just an inexpensive piece "+
    "of jewelry with a broken chain.  A shiny red gem is set "+
    "into a golden wire cage.  The gold wires of the cage are "+
    "dull and faded with age, and the clasp of the chain is broken.\n");
  add_prop(OBJ_I_WEIGHT,550+random(100));
  add_prop(OBJ_I_VOLUME,300);
  add_prop(OBJ_I_VALUE,250+random(100));
  add_prop(SHIRE_SHIP_QUEST,1);
}
