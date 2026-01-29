/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * wpier_s.c
 *
 * The southern end of the western pier.  The ship from Sparkle docks here.
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
    set_long("This is the southernmost end of the western wooden pier. "+
	     "East, beyond the bay, you see another pier. " +
	     "Some distance to the north you see a road and south " +
	     "you see nothing but the sea. There is a distinct " +
        "smell in the air. There is a sign here.\n");
    
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
    add_item("sign","The sign reads: Passage to Sparkle\n");
    add_cmd_item("sign","read","Passage to Sparkle.\n");

    add_exit(PORT_DIR + "wpier_n", "north", 0);



    boat = clone_object(SHIP_DIR + "t_ship");
    boat->move(TO);

    set_alarm(2.0, -1.0, "start_boat", boat); 
}

/*
 * Function name: start_boat
 * Description:   Start up the boat
 */
public void
start_boat(object boat)
{
    if (boat && present(boat, TO)) 
	boat -> start_ship();
}



