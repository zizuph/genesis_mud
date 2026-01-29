inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

create_room()
{
	set_short("On a grassy field north of a large hill");
	set_long(
		"You are walking on a grassy field, north of a large hill. The "+
		"hill can be seen a few miles to the south. The road seems to lead "+
		"into some heavy bushes just west of here. East it continues towards "+
		"a forest. The plains stretches out for a long distance north, many "+
		"leagues, and southwards it seems to end at that large hill.\n");
	ITEM("field", "The grassy field seems to endlessly go north. But it propably "+
		"ends up near Fornost, or the North Downs.\n"); 
	ITEM("hill", "You see a small hill a few miles south. That must be the Bree-hill "+
		"where hobbits and men live together.\n");
	ITEM("road", "The road is paved, and well used it seems. It is leading "+
		"towards some bushes west of here and towards a forest east of here.\n");
	ITEM("bushes", "The bushes is where the road leads. Maybe it ends up there?\n");
	ITEM("forest", "A rather large forest can be seen some miles eastwards. It "+
		"is called the Chetwood.\n");
	add_exit(BREE_DIR +"archet/archet1", "west", 0, 2);
	add_exit(BREE_DIR +"archet/archet3", "east", 0, 1);
}

