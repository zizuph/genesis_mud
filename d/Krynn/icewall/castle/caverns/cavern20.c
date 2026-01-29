/*Created by Stevenson*/

/* create an object called stalactite that will have commands like
touch, knock, break, etc that the player can obtain the gem
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object stalac;

string my_desc();

reset_icewall_room() {
   if (!stalac) {
      stalac = clone_object(ICE_CAST_O+"stalac");
      stalac->move(TO);
   }
}

create_icewall_room()
{
   set_short("Stalactite Room");
   set_long("@@my_desc");

   add_item("stalactites","Some are short, some are long, some are fat, "
      + "some are skinny. . . Say, shouldn't you be doing something right "
      + "now?\n");
   add_item("floor","It is smooth.\n");
   add_item("ceiling","It is covered with hundreds of stalactites.\n");
   
   add_exit(CAVERNS+"cavern19.c","northwest");
   add_exit(CAVE+"cavern18.c","west");
   
   reset_icewall_room();
}

string
my_desc()
{
    string desc;
    desc = "This room is rather barren but directly overhead are hundreds of "
      + "stalactites of every possible description aiming down at the "
      + "ground. Some look rather loose and would cause some pain in "
      + "your body if they were to pierce you.";

    if (present("_stalactite_", TO))
      desc += " One stalactite is long enough that you can touch it.";

    return desc + "\n";
}

