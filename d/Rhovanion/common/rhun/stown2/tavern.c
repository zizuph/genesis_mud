inherit "/std/room";
inherit "/lib/pub";
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Abandoned tavern");
  set_long("The interior of this abandoned tavern"
          +" is especially sparse and vacant. The owner has apparently"
          +" sold off everything he could to save his business."
          +" There is a menu here which you may read. The only"
          +" exit leads back out to the north.\n");

  add_item("menu","The menu was meant to be read.\n");

  add_exit(RHUN_DIR+"stown2/road_sw","north",0);

  add_cmd_item("menu", "read", "" +
    "   Fine imported whiskey             100 cc\n" +
    "   Tender venison strips              18 cc\n" +
    "");

  add_prop(ROOM_I_INSIDE, 1);

  add_drink(({"whiskey","stale whiskey"}), "whiskey", "stale", 150, 15, 100,
            "stale whiskey", "stale whiskeys",
            "This whiskey looks like it has been sitting for a long time.\n");
  add_food(({"venison","tender venison","tender venison strips",
             "venison strips","strips"}),"venison","tough",90,18,
           "tough venison","tough venisons",
           "It seems like the cook intentionally picked the worst deer he "+
           "could find for this piece.\n");
}

void init()
{
    ::init();
    init_pub();
}
