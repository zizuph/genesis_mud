#include "/d/Shire/common/defs.h"
inherit SHIRE_DIR +"room";

create_room()
{
	set_short("At the edge of a forest");
	set_long(
		"You are standing at the edge of a rather large forest. A road "+
		"is leading east further into it. Green, grassy fields, with "+
		"some additional trees spread out westwards, and some miles south "+
		"a small part of a hill can be sighted. Something that looks "+
		"like a hedge seems to encircle the hill. A road goes westwards "+
		"over the green field.\n");
	ITEM("forest", "The forest is called Chetwood, an old forest that has "+
		"survived the great changes during the first and second age of the "+
		"sun.\n");
	ITEM("road", "A dusty, paved road which seems to be used alot. It "+
		"goes east into the forest Chetwood, and west over a green field.\n");
	ITEM(({"field", "fields"}), "The green fields stretch out westwards, and "+
		"seems to go on forever.\n");
	ITEM("trees", "Mainly oak trees can be found around here, but some "+
		"firs can also be spotted.\n");
	ITEM("hill", "That must be the Bree-hill, where the center of the Bree-land "+
		"is sited.\n");
	ITEM("hedge", "A hedge is encirceling Bree, to keep unwanted people out "+
		"of the town.\n");
	add_exit(BREE_DIR +"archet/archet2", "west", 0, 1);
	add_exit(BREE_DIR +"archet/archet4", "east", 0, 1);
	man = clone_object(BREE_DIR +"npc/tim_ber");
	man->arm_me();
	man->move(TO);
	tell_room(ETO, QCTNAME(man)+" arrives from the forest.\n");
	reset_room();
}

set_noshow_obvious();

void
reset_room()
{
	if (!present(objectp(man)))
	{
		man = clone_object(BREE_DIR +"npc/tim_ber");
		man->move(TO);
		man->arm_me();
		tell_room(ETO, QCTNAME(man)+" arrives from the forest.\n");
	}
}
