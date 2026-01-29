inherit "/std/scroll";
#include "/sys/stdproperties.h"

create_scroll()
{
  set_name("scroll");
  set_adj("paper");
  set_adj("brown");
  set_short("brown paper scroll");
  set_long("This brown paper scroll contains several lines of writing.\n"+
    "You feel like reading it.\n");
  set_file("/d/Gondor/elessar/quest/revealspy/scroll.txt");
}
