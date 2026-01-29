inherit "/d/Emerald/ctower/room/ctower_base";
 
#include "../ctower.h"
#include <stdproperties.h>
 
void
create_ctower_room()
{
    object door;
   
    set_short("Tower hall");
   
    set_long( "The walls of this hallway give off a soft "+
	"glow\nthat gives everything an unreal appearance.\n" );
   
    add_item(({"wall", "floor", "ceiling"}), "The walls are made of a "+
	"milky crystal that is cold to the touch.\n");

    add_exit(CTOWER_ROOM + "hall7", "south");
    add_exit(CTOWER_ROOM + "room4", "north");
   
    door = clone_object(CTOWER_OBJ + "door1_a");
    door->move(this_object(), 1);
  
    door = clone_object(CTOWER_OBJ + "door2_a");
    door->move(this_object(), 1);
   
    add_item(({"door","crystal_door"}),  "The door is made "+
	"of a transparent crystal that looks fragile but isn't and has a "+
	"lock made out of what appears to be rubies.  Maybe you should "+
	"examine a specific door.\n" );
   
    add_item(({"east door"}),  "When you examine the "+
	"east door more closely you notice that it is occupied by a "+
	"pathetic, starved prisoner chained to the wall.\n");
   
    add_item("prisoner", 
	"The prisoner is a sorry example of humanity "+
	"that looks like he could die any minute.\n" +
	"The prisoner says: Go north and up the stairs "+
	"to the top floor, and you will find what you are looking "+
	"for.  If you release me, I will tell you more.\n");
   
    add_item(({"west door"}),  "When you examine the "+
	"west door more closely you notice that it is occupied by a "+
	"hideous, powerful daemon roaming the cell.\n" );
   
    add_item("daemon", 
	"The daemon looks to be vicious, powerful and "+
	"ready for a fight.\n" +
	"The daemon says: For pity's sake, please release me!\n");
   
    add_prop(OBJ_S_WIZINFO,  "These doors aren't what they "+
	     "seem to be. The door where you can see the prisoner is "+
	     "really holding the daemon which will trap the unwary.\n" );

}
