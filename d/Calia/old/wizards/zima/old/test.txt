inherit "/std/workroom";
#include "/d/Dville/abbrev.h"

void
create_workroom()
{
    set_short("Guido's workroom");
    set_long(BS(
        "This is Guido's spherical workroom.  " +
        "The room is perfectly round, you notice many doors with labels " +
        "on them.  There is also a workbench floating in the center of the " +
        "room, and a large cat's bed on the floor.\n"));
    add_exit("/d/Genesis/start/human/town/tower", "human", 0);
    add_exit("/d/Genesis/wiz/entrance", "news", 0);
    add_exit("/d/Genesis/wiz/idea", "idea", 0);
    add_exit("/d/Genesis/wiz/discuss", "discuss", 0);
    add_exit("/d/Genesis/wiz/admin", "admin", 0);
    add_exit("/d/Genesis/wiz/post", "post", 0);
    add_exit("/d/Dville/workroom", "meet", 0);
    add_exit("/d/Dville/glykron/palace/guild", "guild", 0);
    add_exit("/d/Dville/common/entrance", "common", 0);
    add_exit("/d/Krynn/solace/guild/hall1", "solamn", 0);
    add_exit("/d/Kalad/roxxanne/workroom", "roxxie", 0);
    add_item(({"workbench", "bench"}), BS(
       "The workbench is floating magically in the air.  You notice " +
       "many beakers, flask and test tubes filled with liquids, herbs " +
       "and other assorted spell items.  You decide " +
       "not to touch anything.\n"));
    add_item(({"beakers", "flasks", "test tubes", "herbs", "liquids"}), BS(
       "These are Guido's ingredients for creating rooms, monsters, " +
       "and anything else he can think of.  He'd probably be a little " +
       "ticked if someone messed with them.\n"));
    add_item(({"cat's bed", "bed", "large bed", "large cat's bed"}), BS(
       "The bed is covered with white lion hair. You decide not to " +
       "touch it, in fear of angering its owner.  There is some writing " +
       "on the side.\n"));
    add_item(({"writing"}), BS(
       "It says: Zax the White Lion.\n"));
}
