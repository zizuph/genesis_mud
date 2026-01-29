inherit "/std/scroll";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#include "defs.h"

#define SCROLL_TEXT AVENIR_LINE + "sign1.txt"

void
create_scroll()
{
    set_name("sign");
    set_short("wooden sign");
    set_long("You are looking at a wooden sign attached to the "+
      "pier. It has a beautiful symbol carved into the wood.\n");

    set_file(SCROLL_TEXT);
    add_prop(OBJ_I_NO_GET, 1);
}
