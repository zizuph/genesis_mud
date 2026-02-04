/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * spier_1.c
 *
 * Pier to nowhere 
 * Goldberry July 14, 1999
 */

#include "/d/Terel/include/Terel.h"
#define DAB_HARB DABAAY_DIR + "harbor/"

#define LIFT_LOG "/d/Terel/dabaay/log/plank"

inherit DAB_HARB + "port_room";

init()
{
    add_action("lift", "lift");
    ::init();
}

lift(string str)
{
   string lifter;

   if (str!="plank") return 0;
   write("You carefully lift up the loose plank.\n");
   write("Lifting the plank opens a hole beneath your feet!\n");
   say(QCTNAME(this_player()) + " disappears through the pier!\n");
   tell_room(DABAAY_DIR + "harbor/un_pier1",
     QCTNAME(this_player()) + " drops down from above.\n");
   this_player()->move_living("M", DABAAY_DIR + "harbor/un_pier1");
   
   lifter = TP->query_name() + "[" +TP->query_average_stat() + "]";
   write_file(LIFT_LOG, lifter + " (" + ctime(time()) + ")\n");
   return 1;
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("At the end of a short pier");
    set_long(
        "This is a wooden pier on the southwestern side of the docks. "+
        "To the south you can see the southern part of the bay spanning "+
        "out to where the south shore is just visible over the horizon. "+
        "The pier stretches out from the north, where you can see the "+
        "main boardwalk of the docks.\n"+
	"There is a small sign here.\n");
    
    add_item("sign",
        "The wooden sign has several words carved on it. "+
        "It is mounted on a stout wooden pole that is "+
        "seated in a hole in the planks at your feet.\n");
    
    add_item("planks",
        "Rough-sawn and weather-beaten, the planks you are on "+
        "seem sturdy and true. On closer inspection, one plank "+
        "appears to be a bit loose.\n");

    add_item("plank",
        "A rough-sawn and weather-beaten plank of wood. The pier "+
        "has many of them.\n");

    add_item(({"pier", "wooden pier"}), 
        "It's a well-built wooden pier. It will withstand the " +
        "worst of storms.\n");
    
    add_item(({"bay"}),	
        "You can see some fishing boats that have anchored in the "+
        "midst of the bay. Out towards the east and past some other "+
        "piers, the bay opens into the sea. From this distance, you "+
        "can barely make out what appears to be a stone wall "+
        "stretching from the north shore into the bay.\n");
    
    add_item(({"sea"}), "It looks cold and blue.\n");

    add_item(({"wall","stone wall"}), 
        "It is difficult to make out any details from this distance. "+
        "Every few moments a wave crashes over the wall.\n");
    
    add_cmd_item("sign","read",
		 "Due to numerous acts of thievery, pickpocket\n"+
		 "and passenger harm, the routes from Dabaay have been\n"+
		 "reduced to a single line to Last in the middle north\n"+
		 "pier.\n"+
		 "\n-- Genesis ShipLines Company\n");

    add_exit(DAB_HARB + "bwalk_1", "north", 0);

}

