inherit "/std/scroll";
#include "/sys/stdproperties.h"

create_scroll()
{
  set_name("book");
  add_name("notebook");
  set_adj("little");
  set_short("little notebook");
  set_long("This is a small notebook with some writing in it. Maybe you can\n"+
    "read it?\n");
  set_file("/d/Gondor/elessar/quest/revealspy/notebook.txt");
}
