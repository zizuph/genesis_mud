#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

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
	"great oaks","oaks","ancient oaks","thick underbrush","underbrush",
	"shadows","trees"}),
      "Surrounding you is an ancient evergreen forest of great " +
      "oaks and thick underbrush. Sounds echo from the shadows " +
      "give the forest a forboding aspect.\n");
    add_item(({"bridge","merrily flowing river","river"}),
      "To your east you see a bridge crossing a merrily " +
      "flowing river.\n");

    add_invis_exit(FROOM + "nowhere","north","@@no_go");
    add_invis_exit(FROOM + "nowhere","south","@@no_go");
    add_exit(FROOM + "bridge","east",0);
    add_exit(FROOM + "road12","west",0);

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
    "you are not welcome here. To the east you see a " +
    "bridge crossing a merrily flowing river.\n";
}


int
closed()
{
    write("The trees close in around you as you try to enter the " +
      "lands of Kendermore, blocking the road to the east.\n");
    return 1;
}
int
no_go()
{
    write("Thick underbrush impedes travel in that direction.\n");
    return 1;
}

int
enter_forest()
{
    write("You step off the road and into the forest...\n");
    return 0;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
	start_room_tells();
}
