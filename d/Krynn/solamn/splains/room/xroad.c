/* created by Aridor 06/21/93 */

#include "../local.h"
#include "../dragon/local.h"

inherit OUTSIDE_BASE;

create_splains_room()
{
    set_short("Crossroads");
    set_long("This is a crossroad. Towards the east, you cannot make out " +
      "anything special, but nonetheless a path leads this way. " +
      "To the north you can see a huge fortress, surrounded by a moat," +
      " to the west is a bridge and to the south " +
      "the road continues. There are signs pointing " +
      "in all directions.\n");

    add_exit("/d/Krynn/guilds/knights/guildhall/rooms/bridge", "north");
    add_exit(ROOM + "bridge","west");
    add_exit(ROOM + "road9","south");
    add_exit(LANDING1,"east");

    add_item("signs",BS("There is a north, a south, an east and a west sign.",SL));
    add_item("sign",BS("Which sign do you want to look at?",SL));
    add_item("north sign",BS("You can read:  VINGAARD KEEP.",SL));
    add_item("south sign",BS("The south sign says:  HARBOUR.",SL));
    add_item("west sign",BS("The sign to the west reads:  PALANTHAS.",SL));
    add_item(({"east sign","eastern sign"}), "The sign pointing east says:" +
      " The bronze dragon to SOLACE has retired. Seek another way.\n");
    add_item(({"fortress","keep"}),BS("It is a keep surrounded by very high stone "
	+  "walls.",SL));
    add_item(({"bridge","river"}),BS("You can see that there is bridge over the "
	+  "river to the west.",SL));
    add_item(({"moat"}),BS("The moat is connected to the river in the west and "
	+  "continues along the walls of the keep to the east.",SL));
    add_item(({"wall","walls"}),BS("The walls are just too high. Don't even consider "
	+  "climbing them. They are made from stone.",SL));
    add_cmd_item("signs","read",BS("There is a north, a south and a west sign.",SL));
    add_cmd_item("sign","read",BS("Which sign do you want to look at?",SL));
    add_cmd_item("north sign","read",BS("You can read:  VINGAARD KEEP.",SL));
    add_cmd_item("south sign","read",BS("The south sign says:  HARBOUR.",SL));
    add_cmd_item("west sign","read",BS("The sign to the west reads:  PALANTHAS.",SL));
    add_cmd_item(({"east sign","eastern sign"}),"read", "The sign pointing" +
      " east says: The bronze dragon to SOLACE has retired. Seek another way.\n");
}
