inherit "/std/room";

#include "/d/Emerald/defs.h"

create_room()

{
    catch(call_other("/d/Emerald/sanctuary/center/clone_handler", "??"));
    set_short("Small alley");

    set_long("   A dreary alley, deep in the center of Sanctuary; " +
      "dark shadows veil this confining path as the walls loom over " +
      "you, making you unsure of which direction you came from and " +
      "which direction will lead you out of these murky passageways. \n\n");

    add_exit("c6", "east", 0, 2);
    add_exit("c4", "west", 0, 2);
    add_exit("/d/Emerald/sanctuary/o1.c", "northwest", 0, 2);

}
