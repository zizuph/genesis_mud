inherit "/std/object";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_object()
{
  set_short("carved wooden heart");
  set_name(({"carving","heart","_woodcutter_quest_carving"}));
  set_adj(({"carved","wooden"}));
  set_long("This heart is carved from a piece of wood. Although it is very "+
           "simple you can see a great skill with which it was made.\n");
}
