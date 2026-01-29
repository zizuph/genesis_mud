/* highpass */

#include "/d/Shire/misty/local.h"

inherit SHIRE_ROOM;

void
create_shire_room()
{
	set_short("In a glade at the foot of the mountains");
	set_long("You are at the foot of the Misty Mountains. To the west you can see only huge peaks. You are off the path, among some tall pine trees. There is a broad wall of rock here at the mountain's foot.\n");
	
	add_item("peak", "The peaks are high and dark.\n");
	add_item("peaks", "The peaks are high and dark.\n");
	add_item("saddle", "It is a natural saddle between two high peaks.\n");
	add_item("glade", "There are mostly pine trees here at the foot of the mountains.\n");
	add_item(({"trees", "pine trees", "tall trees", "tall pine trees"}), "They are quite tall indeed, although somewhat bare looking, as if they are not healthy.\n");
	add_item(({"wall", "broad wall", "rock wall"}), "The rock wall is thrust out from the side of the mountain, nearly perfectly sheer, almost as high as the trees in the glade.\n");
	
	add_exit("/d/Shire/misty/orc_area/oa4", "east", 0, 5);
	add_exit("/d/Shire/misty/orc_area/oa6", "north", 0, 5);	

}
