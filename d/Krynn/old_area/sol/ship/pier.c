#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>

inherit SOLOUTROOM;

void add_stuff();

object ship;

void
create_solace_room()
{
   set_short_desc("on a pier in Crystalmir Lake");
   set_extra_line("This pier looks ancient and abandoned, now " +
      "only used by local fishermen, instead of world travellers. " +
      "Occasionally, a villager will come by with a rowboat to give " +
      "those willing to pay the price passage to Newports. East is " +
      "a road leading back to Solace.");
   
   add_prop(ROOM_I_NO_CLEANUP,1);
   add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is stuck, type " +
      "'Call here restart_ship <reason>'.\n");    
   
   add_exit(C_SOLACE, "east");
   
   add_item("pier", "The pier is built on huge boulders. How they got here " +
    "is a mystery. The pier is now only used by the local people.\n");
   add_item(({"water","lake"}),
      "This is Crystalmir Lake, stretching out wide to the " +
      "north and south. The opposite shore to the west can barely be " +
      "seen, all you can make out are some mountains over yonder.\n");
   add_item("mountains", "They are too far away to see any details.\n");
   add_item("opposite shore","It is too far away to see any details.\n");
   add_item("boulders","They're hard rock.\n");
   add_item(({"road","track"}),
      "This is more like a track, apparently leading to the village " +
      "of Solace.\n");

    reset_room();
   
}

void
add_stuff()
{
   seteuid(getuid(this_object()));
   if (!ship)
      {
      ship = clone_object(OBJ + "ship");
      ship->start_ship();
   }
}

void
reset_room()
{
   add_stuff();
}

void
restart_ship(string reason)
{
   if (!reason)
      {
      write("Can't restart the ship without a reason.\n");
      return 0;
   }
   (ship->query_captain())->remove_object();
   ship->remove_object();
   add_stuff();
   write_file("/d/Krynn/common/log/shiprestart", extract(ctime(time()), 4, 15)
      + " Solace-Newport " + capitalize(this_player()->query_real_name()) + " " + reason + "\n");
   write("Ship restarted.\n");
}



