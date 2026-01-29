inherit "/std/scroll";
#include "/sys/stdproperties.h"

create_scroll()
{
  set_name("parchment");
  set_adj("wrinkled");
  set_adj("yellowed");
  set_short("yellowed, wrinkled parchment");
  set_long("This yellowed, wrinkled piece of parchment must have been written\n"+
    "many years ago. You notice that the writing on it is in a dark red\n"+
    "colour.....blood??\n");
  set_file("/d/Gondor/elessar/quest/revealspy/parchment.txt");
}
