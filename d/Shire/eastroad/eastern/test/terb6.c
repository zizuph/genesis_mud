#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
    set_area("outside the Forsaken Inn between the Chetwood "+
      "and the Midgewater Marshes on");
    set_areaname("the Great East Road");
    set_land("Eriador");
    set_areatype(AREATYPE_ROAD);
    set_areadesc("open field");
    set_grass("wet long");
    set_treetype("oak");

    set_extraline("The dense oak forest swallows up the road to your "+
      "northwest, where in all other directions the view is pretty clear, "+
      "except to the far east where you can make out the pall hanging "+
      "over the Midgewater Marshes. Standing glumly on the south side of "+
      "the road is the Forsaken Inn, a ruined shadow of its former glory "+
      "of hundreds of years ago. The road continues to the northwest "+
      "and east from here.");

    add_item(({"inn","forsaken inn"}),
      "Lurking over the Great East Road here is the famous Forsaken "+
      "Inn. Hundreds of years ago it was a favourite drinking hole "+
      "for the many folk of Arnor travelling from one place to "+
      "another, but since the destruction of Fornost the Inn has "+
      "fallen into ruin.\nIts once healthy and strong timber is now "+
      "cracked and grey, and most of the roof shingles have crumbled "+
      "and cracked, allowing free flow of rain to run through to the "+
      "ground floor and wreak a slow havoc there. The front door of "+
      "the Inn is locked and barred, but you can make out a hole in "+
      "the west wall from where you can enter the Inn.\n");
    add_item(({"hole","wall","west wall"}),
      "An apparent weakness in the west wall of the Inn has allowed "+
      "further decay, now leaving a fairly large hole. Seeing that "+
      "the front door is locked and barred, you can use the hole to "+
      "enter the Inn.\n");
    add_item(({"forest","chetwood","oak forest"}),
      "The ancient oaks of the Chetwood swallow up the Great East road "+
      "with the heavy tree cover almost plunging the forest into "+
      "darkness.\n");
    add_item(({"pall","marshes","midgewater marshes"}),
      "All that is visible of the Midgewater Marshes from this distance "+
      "is the haze hanging over the horizon, and the occasional whiff "+
      "of the foul smell of rotten gasses.\n");

    add_exit(ER_DIR + "erb5",  "northwest", 0, 1);
    add_exit(ER_DIR + "erb7",  "east", 0, 1);
    /*  add_exit(ER_DIR + "erb5s", "west", 0, 2, 1);
	add_exit(ER_DIR + "erb6n", "north", 0, 2, 1);
	add_exit(ER_DIR + "erb6s", "south", 0, 2, 1); */

}

void init()
{
    ::init();
    add_action("enterinn", "enter");
}

int enterinn(string inn)
{
    notify_fail("Enter what?\n");

    if (inn!="inn") return 0;
    write("You slip through the hole in the west wall and enter "+
      "the Forsaken Inn.\n");
    say(QCTNAME(TP)+" enters the Inn through a hole in the west wall.\n");

    TP->move_living("into the Inn", "/d/Shire/eastroad/eastern/inn1");

    return 1;

}
