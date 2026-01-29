/*Created by Macker 7/11/94*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit VILLAGE_OUTROOM;

create_village_room() {
	set_short("Village");
   set_long(
	"You are standing on the hard, icy ground of the ice folks' " +
	"tiny village. There are quite a few small tents around, and "+
	"there is a relatively large ice building to your east. " +
	"The road, which is more like a path, leads northeast and " +
	"southeast.\n");
   
	add_item( ({"snow", "ice", "road", "path", "ground"}), 
	"It is white and cold. What did you expect?\n");
	add_item( ({"building", "large building"}), "" +
		"The building to the east is much larger than the tents " +
		"you see all around you. You see no entrance to the building, so " +
		"it is probably on one of the other sides. " +
		"You see some smoke rising from the roof of the building.\n");
	add_item( ({"roof", "smoke"}),
		"You see smoke rising from the roof and decide there must be a " +
		"fire inside the building. It makes you want to go inside and warm up.\n");
	add_item("village", "You are in the village, you silly person. Just look around!\n");
	add_item("tracks", "You see tracks in the snow everywhere you look. " +
	"\n");
	add_item("tents", "There are quite a few here, but they seem " +
		"unimportant. They are probably just used as " +
		"quarters for the poorer families.\n");
	add_item("buildings", "These buildings are made entirely of packed, " +
		"frozen snow. They will never melt because it is always " +
	"freezing here! You will probably enter a few of these buildings " +
		"if you continue to stroll through the village.\n");
	add_item( ({"people", "folk", "ice folk", "ice people"}),
		"The ice folk you see are wrapped tightly in hides from " +
		"various animals. Their faces look worn from the years spent " +
		"in this harsh environment. Surprisingly they do not look unhappy. " +
		"In fact, they seem to be content with their lives in this frozen wasteland. You are sure they have their share of problems though.\n");

add_exit(VILLAGE +
	"village_2.c", "southeast");

add_exit(VILLAGE +
	"village_4.c", "northeast");
}

