#pragma save_binary

inherit "/std/scroll";
#include <stdproperties.h>
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

create_scroll()
{
   seteuid(getuid(this_object()));
set_name(({"map","_armour_quest_map"}));
   set_short("tattered map");
   set_long("This is a brown, tattered map that is mostly " +
      "ruined from exposure from the elements. Still, there is " +
      "a bit of text left on it that could be read.\n");
   set_file(MAP_FILE_ONE);
}
