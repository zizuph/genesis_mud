/*
 *  sea osprey's aerie
 *  coder: Tigerlily
 *  date:  2001-12-27
 *  notes: 
 *
 */

#pragma strict_types
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>

#include "defs.h"


int climb_boulders(string str);

void
create_room()
{
    set_short("osprey's aerie");
    set_long("Situated on a lofty, narrow crag of rock high"+
      " above the sea, you are buffeted by gales of wind"+
      " and have difficulty maintaining a foothold."+
      " Clearly this is a place where birds are more at home."+
      " There is a wide view here of the entire region.\n");

    add_item(({"crag", "clifftop", "surface"}), "This lofty crag"+
      " sits high upon a cliff overlooking the Calian sea. The narrow"+
      " ledge of the clifftop is set back against a wall of granite."+
      " It supports a platform of large granite"+
      " boulders containing an osprey's nest.\n");
    add_item(({"view", "region", "sea"}), "You gaze"+
      " out onto the beautiful Calian"+
      " sea. Far away to the north you can see the harbour"+
      " of Gelan. To the east the peak of Mount Kyrus"+
      " is shrouded in mist. To the west"+
      " the sea extends all the way to the horizon."+ 
      " As you look directly down the cliff, however, you get"+
      " a giddy feeling of vertigo realizing how far down your fall"+
      " would be.\n");
    add_item("mist",
      "To the east mist encroaches on the moors and crowns the"+
      " peak of Mount Kyrus.\n");
    add_item(({"harbour", "Gelan", "gelan"}),
      "The harbour of Gelan is busy with sea trade. Brightly"+
      " painted ships periodically enter and leave.\n");
    add_item("horizon",
      "To the west the sea meets the sky at the horizon.\n");


    add_item(({"rock", "granite", "boulders", "boulder",
	"platform"}), "The granite"+
      " boulders have deep cracks between them. To the west they"+
      " are heaped into a raised platform that appears to contain"+
      " a very large bird's nest.\n");

    add_item("nest", "Constructed of twigs, branches, and dried seaweed,"+
      " it apparently belongs to a very large bird. The nest is raised"+
      " on a platform of boulders above your head so that it is"+
      " impossible to look into it from here.\n");

    add_item("cracks", "There are deep cracks between the boulders"+
      " that appear to contain some nasty-smelling debris.\n");
    add_item("debris", "Various types of debris have fallen from"+
      " the bird nest and are lodged firmly between the cracks. You see"+
      " bits of fish leftovers as well as what appears to be ..."+
      " and smells like ... bird excrement.\n");
    add_item(({"excrement", "bird excrement"}),
      "Obviously the osprey family has been living in this nesting"+
      " area for a long time.\n");
    add_item("ledge", "The rough ledge juts out slightly"+
      " from the granite wall right behind that gives some shelter"+
      " from the elements.\n");
    add_item(({"wall", "granite wall", "clifftop"}), "The clifftop wall"+
      " to the south of you ends here. It does not look"+
      " possible to climb it.\n");
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,0);


    add_exit(AERIE + "aerie2", "west",0,0);
    add_exit(CLIFF_ROOM + "cliff2_4", "down",0, 1);


}


void
init()
{
    ::init();
    add_action(&climb_boulders(), "climb");
    return;
}

int
climb_boulders(string str)
{

    if (!str)
    {
	notify_fail("Climb what?\n");
	return 0;
    }

    if (str == "nest" || str == "boulders")
    {
	notify_fail("You must get closer.\n");
	return 0;
    }

    notify_fail("You try to climb " + str +
      " and fall flat on your face!\n");
    return 0;
}

