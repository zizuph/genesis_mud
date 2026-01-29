/*
 * A stall selling soft drink
 * TAPAKAH, 04/2009
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Khalakhor/inisi/roke/lib/pub";

#include "defs.h"

#define CDIR ROKEDIR + "obj/"
void
create_room()
{
  config_pub();
  set_short("A food kiosk on Cadu pier");
  set_long(
           "You are standing next to a small kiosk selling soft drinks. "
           +"There is a pricelist next to the kiosk's window. "
           +"Beyond the window you can see a small gnome smiling at you. "
           +"To the west and east you see piers where ships land.\n" 
           );
  add_item("window", "A small, foot-by-foot square window in this wooden "+
           "kiosk.\n");
  add_item(({"menu", "list", "pricelist"}), "@@read");
  add_cmd_item(({"menu", "list", "pricelist"}), "read", "@@read");
  add_exit("cadu_pier2", "west"); 
  add_exit("cadu_pier3", "east");
  add_article(({"water", "glass of water",}),
              CDIR + "gwater", 6);
  add_article(({"orange juice", "juice", "orange"}),
              CDIR + "ojuice", 18);
  add_article(({"iced tea", "tea"}),
              CDIR + "itea", 36);
  INSIDE;
  reset_room();
}

void
init()
{
    ::init(); 
    init_pub();
}

string
read(string str)
{
    return
        "   Glass of Water               6 copper\n" +  
        "   Orange Juice                18 copper\n" +  
        "   Iced Tea                     3 silver\n" +  
        "\n" + pub_std_usage_string();
}

int
pub_hook_may_order()
{
    return 1;
}
