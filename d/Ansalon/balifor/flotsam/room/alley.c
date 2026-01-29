/* Adapted by Torqual */
/* starting point for wagon between Flotsam and Neraka */


#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_OUT;

/* includes */
#include <macros.h>

/* defines */
#define WAGON_FILE "/d/Ansalon/balifor/flotsam/obj/wagon/wagon.c"

/* prototypes */
int fetch_wagon(string wagon_file);

create_flotsam_room()
{
    set_short("alleyway in Flotsam");
    set_long("@@long_descr");

    add_item(({"filth","garbage","rubbish"}),"You name it, if it " +
      "smells bad, your standin' in it! \n");

    add_item(({"alley","alleyway"}),"You stand in a dark alleyway. " +
      "Dirty brick walls run along, ending at the south with a stone one. "+
      "Northeast opens up on the main street. The alley is unusually" +
      " wide and there are deep wheel-tracks on the ground.\n");

   add_item(({"ground", "tracks", "wheel-tracks"}),
      "The soil under your feet is covered with many deep wheel-tracks. "+
      "It looks like wagons stop here very often.\n");

    add_item("vermin","Glowing red eyes stare at you from the " +
      "darkness, giving you the impression that you are not " +
      "wanted here. \n");

    add_item(({"wall", "walls"}), "Which wall? The stone one or the " +
      "brick one?\n");

    add_item("stone wall", "The stone wall is a part of city " +
      "defences. It rises high up above your head and seems to be " +
      "unscalable. It connects with two more brick walls.\n");

    add_item(({"brick wall", "brick walls"}), 
      "The walls on your left and right are solid, high and dirty. " +
      "Dark patches cover both of them from the top to the bottom, " +
      "with few red spots showing that the walls are really made of " +
      "bricks.\n");

    add_item(({"patches", "dark patches"}), "You come closer to look at "+
      "the dirt on the one of the walls and discover that it is " +
      "nothing more then dust that has settled on the bricks. Some " +
      "darker stain can be seen in the corner, just above the ground.\n");

    add_item(({"stain", "dark stain", "darker stain"}), "Just above "+
      "ground level you notice the corner of the wall is wet and ... stinking. "+
      "Looks like someone urinated here.\n");
    add_item("bricks", "You cannot see much of them under the layer of " +
      "dirt but they seem solid and quite old.\n");


    add_exit(FROOM + "street42","northeast",0);


    fetch_wagon(WAGON_FILE);
}

string
long_descr()
{
    return tod_descr1() + "You stand amidst the filth and " +
    "garbage of one of Flotsam's many alleys. Vermin skitter " +
    "into the rubbish as you pass through. The main street is "+
    "to the northeast, while to the south the alley ends in a " +
    "stone wall.\n";
}

int
fetch_wagon(string wagon_file)
{
    object wagon_obj;

    /* we return 0 if failed to load the file, 1 - if we managed */

//    if (LOAD_ERR(wagon_file))
//     return 0;

    find_player("torqual")->catch_msg("DEBUG: WAGON name " + wagon_file +
        "\n");

    wagon_obj = clone_object(wagon_file);
    wagon_obj->move(TO);
    wagon_obj->start_moving();
    return 1;
}
