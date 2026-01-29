inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"


object board;

void
create_room()
{
    if (!present("board")) /* Clone our own board if necessary */
    {
	board = clone_object(SHIRE_DIR + "boards/domain");
	board->move(this_object());
    }
    set_short("Shire domain room");
    set_long("This ancient room is a meeting place for the "+
      "wizards of the Shire.  Here many weighty decisions "+
      "are made, and many frivolous jokes told.  A plaque on the "+
      "wall attracts your interest.  South is the entrance "+
      "to Tech's tower and to the west is the Middle Earth "+
      "discussion room, where you can learn more about "+
      "Tolkien's world.\n");

    add_exit(SHIRE_DIR + "ME_DISCUSS","west");
    add_exit("/d/Gondor/ME_ideas", "southeast", 0);
    add_exit(SHIRE_DIR + "private/me_private", "north");
    add_exit(COMMON_DIR + "domain_entr","south",0);

    add_prop(ROOM_I_INSIDE,1);

}

