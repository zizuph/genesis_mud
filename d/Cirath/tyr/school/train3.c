#include "/d/Cirath/common/defs.h"
inherit "/std/room";
#include "wbt.h"

void
create_room()
{
   set_short("West Corner of Training Hall");
   set_long("This is the western side of the large training "
	+"hall in the Warriors School of Tyr.  You see a few "
	+"adepts training with cheap weapons here, trying to "
	+"impress the instructors.  The only other thing of any "
	+"note here are the simple wooden dummies and racks "
	+"filled with training weapons.\n");
   add_item(({"adept","adepts"}),"They look to be mostly young "
	+"men and women who are trying to learn the basics of "
	+"combat and tactics.\n");
   add_item("weapons","You see a variety of wooden and bone "
	+"practice weapons.  The variety includes axes, maces, "
	+"and swords.\n");
   add_item(({"dummies","dummy"}),"The training dummies here "
	+"appear to be crafted from cloth, wood, and some sort "
	+"of stuffing.\n");
   add_item(({"rack","racks"}),"They are made from sturdy wood "
	+"and contain a variety of weapons.\n");

	INSIDE;

	add_exit(WWORK+"train5.c", "north", 0, 0);
	add_exit(WWORK+"train1.c", "east", 0, 0);
}
