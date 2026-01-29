#pragma save_binary

inherit "/std/scroll";
#include <stdproperties.h>
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

create_scroll()
{
   seteuid(getuid(this_object()));
   set_name("scroll");
   add_name("mist_map");
   set_adj("papyrus");
   set_short("papyrus scroll");
   set_long("This papyrus scroll contains the flowing script " +
      "of a centaur shaman. Perhaps you should read it?\n");
   set_file(MAP_FILE_TWO);
}
