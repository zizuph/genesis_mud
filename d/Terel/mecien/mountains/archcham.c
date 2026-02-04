inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO  this_object()
#define TP  this_player()

public void
create_room()
{
   set_short("Arch Chamber");
   set_long(
      "The stone here becomes a strange greenish rock. It's smooth and " +
      "unlike anything else around it. Part of its formation is cut into an " +
      "archway that leads north.\n");

   add_item("archway", "It is cut into the strange aquamarine stone. " +
            "Upon it a winged spirit has been carved.\n");
   add_item("winged spirit", "It is carved into the arch. " +
            "It holds a shield engraved with a tree.\n");
   add_item("shield", "It is part of the carved image.\n");
   add_item("tree", "A mysterious tree imaged on the spirit's shield.\n");

   add_exit("/d/Terel/mecien/mountains/dpas3", "south", 0);
   add_exit(GUILD_DIR + "dc4", "north", "@@arch");
}

public int
arch()
{
   object dragon = find_living("arinosticarus");
   
   if (MEMBER(TP)) return 0;
   if (dragon) {
       dragon->warn();
       TP->catch_msg("You hear a faint sound from the north.\n");
   }
   return 0;
}
