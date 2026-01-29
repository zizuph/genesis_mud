inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {set_short("Divided Sky.\n");
   set_long("You are now in a large rectangular room " +
      "of large, stone blocks approximately fifty feet east and west by " +
      "thirty feet north and south.  Sconches line the " +
      "walls every twenty feet or so providing sufficient " +
      "illumination to see the entire room clearly.\n" +
      "     A dark stone altar lies at the east end of " +
      "the room and sitting on it are two dark stone braziers " +
      "from which the smoke of burning incense is rising. " +
      "Weapon racks line the walls and there's even an " +
      "archery target hung here.  Interrupting the floor in " +
      "the very center of the room is a dark pit.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("target","This is an old round archery " +
      "target painted with three circles and a red bullseye " +
      "in its center.  It bears the scars of the numerous " +
      "arrows that have pierced it.\n");
   add_item(({"sconch","sconches"}),"These stone fixtures jut out " +
      "from the walls each holding a single torch.\n");
   add_item(({"torch","torches"}),"These are short, " +
      "wooden torches wrapped with some highly flammable " +
      "substance at their tips and lit brightly filling " +
      "the room with smoke.\n");
   add_item("altar","This is a small altar about " +
      "three feet in height of dark stone in the eastern end " +
      "of the room.  On it rests a pair of dark stone braziers.\n");
   add_item(({"brazier","braziers"}),"These dark stoned " +
      "bowls are filled with powdered incense which " +
      "is lit and filling the room with a strange, grassy odour.\n");
   add_item(({"rack","racks"}),"These racks are nothing " +
      "more than wooden pegs jutting out from the walls, but " +
      "nevertheless serve their purpose.  They are currently " +
      "empty.\n");
   add_item("pit","You can't see down into the pit " +
      "due to its darkness, but around are set up wooden benches " +
      "perhaps for people to relax on while watching what takes " +
      "place in the pit.  Whatever that may be.\n");
   clone_object("/d/Rhovanion/common/dungeon1/living/wguard5.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/wguard6.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/wguard6.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard18","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/pit","pit");
}
