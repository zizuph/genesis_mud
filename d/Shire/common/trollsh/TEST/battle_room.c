inherit "/std/room";

#include "/d/Shire/orcmaker/orcmaker.h"
#include "/d/Shire/common/defs.h"

create_room()
{
    set_short("Battle test room for monsters and weapons");
    set_long(
    	"You are in a room with no exits. This is the place "
    	+"where the Shire wizards test their upcoming monsters and weapons "
    	+"which are planned for use in the trollshaws. Legs, heads and bodies "
    	+"lay scattered all over the place. Puddles of stained blood can be "
    	+"seen on the floor, as a sign of combat and death! This is not a safe "
    	+"place to be if you are not wizard. You should not be here if you are "
    	+"below wizard level 1!\n");
    	
    add_prop(ROOM_I_LIGHT, 1);

	enable_reset();
	add_stuff();
	reset_room();
}

reset_room()
{
	add_stuff();
}

void
add_stuff()
{
	object orcleader, orc2;

	FIXEUID;

	if (!present("leader"))
	{
		orcleader = clone_object(ORCMAKER_DIR +"orcmaker");
		orcleader->set_long("This seems to be the leader.\n");
		orcleader->add_name("leader");
		orcleader->set_power(120);
		orcleader->set_type(WARRIOR);
		orcleader->move(TO);
		orcleader->team_join(orcleader);
	}
	if (!present("guard2"))
    {
     orc2 = clone_object(ORCMAKER_DIR + "orcmaker");
     orc2->add_name("guard2");
     orc2->set_power(120 + random(20));
     orc2->set_type(GUARD);
     orc2->move(TO);
     orcleader->team_join(orc2);
    }
}
