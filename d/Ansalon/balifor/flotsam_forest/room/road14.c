#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <ss_types.h>
#include <macros.h>

#define LOOK_AT_TRAIL 20
inherit FOREST_OUT;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("On an eroding dirt road through a great forest");
    set_long("@@long_descr");

    add_item(({"road","dirt road","ill-kept dirt road","ill-kept road"}),
      "You stand upon a wide dirt road within a great evergreen " +
      "forest. It looks like it has been a while since anyone " +
      "has done any work on the road, and it seems the underbrush " +
      "has begun to take over it.\n");
    add_item(({"branches","branch"}),"The branches of the great " +
      "oaks sway with the wind.\n");
    add_item(({"forest","evergreen forest","ancient forest",
	"western part of the forest","west","western part",
	"great oaks","oaks","ancient oaks","thick underbrush","underbrush",
	"shadows","trees"}),
      "@@see_trail");
    add_item(({"trail","animal trail"}),"@@animal_trail");

    add_exit(FROOM + "road2","north",0);
    add_exit(FROOM + "road15","south",0);
    add_invis_exit(FOREST_PATH + "/dark_forest/path1","southwest","@@enter_forest");
    add_invis_exit(FROOM + "nowhere","east","@@no_go");
    add_invis_exit(FROOM + "nowhere","west","@@no_go");

    set_tell_time(120);
    add_tell("You hear a growl from the underbrush beside the road...\n");
    add_tell("The ancient oaks groan as a strong wind blows " +
      "through them.\n");

    reset_flotsam_room();
}


string
long_descr()
{
    return "You stand upon an ill-kept dirt road within " +
    "a vast evergreen forest." + tod_descr2() +
    season_descr() +
    " whistles through the branches of ancient oaks, and eerie " +
    "sounds echo from the shadows cast be the trees. Forboding " +
    "noises come from the forest underbrush, adding to the impression that " +
    "you are not welcome here. " +
    "The western part of the forest seems much darker than " +
    "the rest of the forest for some reason. " +
    "\n";
}

int
closed()
{
    write("An overturned cart blocks the way to Port Balifor. " +
      "Perhaps you should come back later when the road is " +
      "reopened?\n");
    return 1;
}

string
see_trail()
{
    if(TP->query_skill(SS_TRACKING) < LOOK_AT_TRAIL)
    {
	return "Surrounding you is an ancient evergreen forest of " +
	"great oaks and thick underbrush. Sounds echo from the " +
	"shadows give the forest a forboding aspect.\n";
    }
    return "Surrounding you is an ancient evergreen forest of " +
    "great oaks and thick underbrush. Sounds echoing from the " +
    "shadows give the forest a forboding aspect. You think you " +
    "notice a well concealed animal trail heading off to the " +
    "southwest.\n";
}

int
no_go()
{
    write("Thick underbrush impedes travel in that direction.\n");
    return 1;
}

string
animal_trail()
{
    if(TP->query_skill(SS_TRACKING) < LOOK_AT_TRAIL)
    {
	return "You find no trail.\n";
    }
    return "You notice a well concealed animal trail heads off into " +
    "the forest to the southwest.\n";
}

int
enter_forest()
{
    if(TP->query_skill(SS_TRACKING) < LOOK_AT_TRAIL)
    {
	write("You cannot find a way through the forest to the " +
	  "southwest.\n");
	return 1;
    }
    else
	write("You skillfully follow the animal trail to your southwest.\n");
    return 0;
}

int
leave_forest()
{
    write("The forest finally ends, and you step out of the gloom of its shadows.\n");
    return 0;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
	start_room_tells();
}
