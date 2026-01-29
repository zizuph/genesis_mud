/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * wpier_n.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit PORT_DIR + "port_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    object boat;

    ::create_room();
    set_short("Western pier");
    set_long("This is a wooden pier. East, beyond the bay " +
	     "you see another pier. North you see a road and by going " +
	     "south you reach the end of the pier. There is a distinct " +
          "smell in the air.\nThere is a sign here.\n");
    
    add_item(({"pier", "western pier", "this pier"}), 
	     "It's made of wooden boards and poles. It looks very " +
	     "robust so it will withstand even the worst of storms.\n");
    
    add_item(({"eastern pier", "another pier", "other pier"}), 
	     "It looks very similar to the one you are standing on " +
	     "right now, but it is hard to judge from this distance.\n");
    
    add_item(({"bay"}), "Out on the bay some fishing boats have anchored.\n");
    
    add_item(({"sea", "water"}), 
	     "The sea looks cold and blue. It covers the whole " +
	     "southern horizon. Gazing south you see no trace of " +
	     "land - only a few sailing ships that are struggling in " +
	     "the brisk and icy wind.\n");
    add_item("sign","A wooden sign nailed to the pier.\n");
    add_cmd_item("sign","read","Ferry to the Enchanted Garden.\n");

    add_exit(PORT_DIR + "road8",   "north", 0);
    add_exit(PORT_DIR + "wpier_s", "south", 0);

    boat = clone_object(SHIP_DIR + "s_ship");
    boat -> move(TO);

    set_alarm(5.0, -1.0, "start_boat", boat); 
}

/*
 * Function name: start_boat
 * Description:   Start up the boat
 */
start_boat(object boat)
{
    if (boat && present(boat, TO)) {
	boat -> start_ship();
    }
}
