
/* 

   /d/Genesis/start/human/town/aoe_scroll.c

   Scroll with <help events> text

   Stern, 13-jan-2001
   
*/ 

inherit "/std/scroll";

#include <stdproperties.h>

#define HELPEVENTS     "/doc/help/general/events"

void
create_scroll()
{
    set_name("parchment");
    add_name("scroll");
    set_adj("sheep-skin");
  
    set_long("The parchment is made from the skin of a sheep, inscribed " +
       "from top to bottom with smooth handwriting in black ink.\n");
    set_file(HELPEVENTS);
    add_prop(OBJ_M_NO_GET, "The scroll is nailed to the table.\n");
    set_no_show_composite(1); /* to hide it from the room */
}
