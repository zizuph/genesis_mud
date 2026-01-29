inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/teamer.h"
#include "wbt.h"

void
reset_room()
{
	::reset_room();
	bring_room_team(WWORK+"adept.c", 1, 2, WWORK+"adept.c", 1);
}

void
create_room()
{
   set_short("East Corner of Training Hall");
   set_long("You are now on the eastern side of the large school "
	+"training hall.  Adepts are present here training with "
	+"various weapons and in various styles.  This side of "
	+"the hall also has its own practice dummies and racks "
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

	add_exit(WWORK+"train6.c", "north", 0, 0);
	add_exit(WWORK+"train1.c", "west", 0, 0);
	set_alarm(1.0,0.0,"reset_room");
}
