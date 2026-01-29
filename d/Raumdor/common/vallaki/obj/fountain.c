/* Sarr */
#include "defs.h"
inherit "/std/object";

void
create_object()
{
    set_name("fountain");
    set_adj("large");
    add_adj("water");
    set_short("large water fountain");
    set_long("This is a large circle of stone filled with water. In the "+
    "center you see a statue of a beautiful mermaid with a large bosom, "+
    "spouting water out of her mouth. The water, clear and blue, flows "+
    "out and down her body into the pool.\n"); 
    add_prop(OBJ_M_NO_GET,"Are you mad?\n");
}

void
init()
{
    ::init();
    add_action("drink_fount", "drink");
}

int
drink_fount(string str)
{
   NF("Drink from what?\n");
   if(str != "from fountain")
       return 0;
   write("You take a gulp of water from the fountain. Ahh!\n");
   say(QCTNAME(TP)+" takes a gulp of water from the fountain.\n");
    TP->drink_soft(TP->query_prop(LIVE_I_MAX_DRINK) / 20);
   return 1;
}

