inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()
#define TO this_object()

static object dragon=0;

public void
reset_room()
{
   if (dragon) return;
   dragon = clone_object(GUILD_DIR + "adragon");
   dragon->move_living("M", TO);
}

public void
create_room()
{
   set_short("Dark Cavern");
   set_long(
      "A huge craggy dark cavern. The walls are covered with soot and ash, as is "
     +"the floor and ceiling. A stone obelisk with silver letters stands in "
     +"the center of the chamber.\n");

   add_exit(GUILD_DIR + "dc1", "east", "@@check");
/*
   add_exit(GUILD_DIR + "dc3", "south", 0);
*/
   add_prop(ROOM_I_LIGHT, 0);
   add_item("obelisk", "It is very large and made of rough stone.\n");
   add_item("letters", "They are silver upon the obelisk.\n");
   add_cmd_item("obelisk", "read",
      "The ages shall not count my days, for so have I " +
      "stood unnumbered since the beginning. Beware, Ye who should walk " +
      "beyond the point of ages, for all who abide here shall seek thee, " +
      "both now and forever.\n");
   reset_room();
}

public int
check()
{
   if (dragon && environment(dragon) == TO) {
      if (TP->query_alignment() < 100) {
          dragon->command("emote moves in front of the east passage, " +
                      "blocking movement through it and " +
                      "starts to rumble with fire.");
          return 1;
      }
      if (MEMBER(TP)) return 0;
      dragon->command("emote raises itself up and blocks movement to the east.");
      return 1;
   }
   return 0;
}
