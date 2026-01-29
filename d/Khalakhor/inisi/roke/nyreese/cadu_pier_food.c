/*
 * A stall selling small food items
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
           "You are standing next to a small kiosk selling snacks and "
           +"sandwiches. There is a pricelist next to the kiosk's window. "
           +"Beyond the window you can see a small gnome smiling at you. "
           +"To the west and east you see piers where ships land.\n" 
           );
  add_item("window", "A small, foot-by-foot square window in this wooden "+
           "kiosk.\n");
  add_item(({"menu", "list", "pricelist"}), "@@read");
  add_cmd_item(({"menu", "list", "pricelist"}), "read", "@@read");
  add_exit("cadu_pier1", "west"); 
  add_exit("cadu_pier2", "east");
  add_article(({"spice cookie", "cookie",}),
              CDIR + "scookie", 12);
  add_article(({"herring sandwich", "sandwich", "herring"}),
              CDIR + "hsandwich", 24);
  add_article(({"fried shrimps", "shrimps"}),
              CDIR + "fshrimps",  24);
  add_article(({"salmon burger", "burger", "salmon"}),
              CDIR + "sburger", 60);
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
        "   Spiced Cookie                1 silver\n" +  /*  64 g */
        "   Herring Sandwich             2 silver\n" +  /* 200 g */
        "   Fried Shrimps                2 silver\n" +  /* 114 g */
        "   Salmon Burger                5 silver\n" +
        "\n" + pub_std_usage_string();
}

int
pub_hook_may_order()
{
    return 1;
}
