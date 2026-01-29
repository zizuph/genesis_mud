inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    object door;
 
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("Temple dungeon");
	set_long("   You have entered the dungeons of the Temple "+
      "of Doom. This is where the monks are kept whenever "+
      "they break the rules of the temple. The punishment is however "+
	"so severe that no one ever breaks them, so the dungeons are " +
      "currently empty. There is a door to the east, while to the "+
	"west the door seems to have been blown away.\n\n");
    add_exit(TEMPLE_DIR + "cell3", "west", 0);
    add_exit(TEMPLE_DIR + "dungeon2", "south", 0);
    door=clone_object(TEMPLE_DIR + "doors/celldoor3_a");
    door->move(this_object());
}
