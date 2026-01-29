#include "/d/Shire/old_forest/defs.h"
inherit "/d/Shire/old_forest/for-g";

void
create_map_room()
{
  ::create_map_room();
  remove_exit("west");
   add_exit("/d/Shire/workroom","west");
}
