/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * bay5.c
 *
 * In the bay, Middle 
 *
 * Goldberry August, 2000
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

#define DAB_HARB DABAAY_DIR + "harbor/"
#define DAB_NPC DABAAY_DIR + "npc/"

inherit DAB_HARB + "port_room";
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Out in the bay");
    set_long(
        "You are swimming in the cold waters of the bay. "+
        "You can see the piers and town to your west. "+
        "The bay continues out to the east.\n");
    
    add_item(({"pier","piers"}),
        "Several large ships are docked at the piers.\n");

    add_item(({"ships","large ships"}),
        "Various cargo ships are docked at the piers.\n");

    add_item(({"bay"}),	
        "You can see some fishing boats that have anchored in the "+
        "midst of the bay. Out towards the east and past some other "+
        "piers, the bay opens into the sea. From this distance, you "+
        "can barely make out what appears to be a stone wall "+
        "stretching from the north shore into the bay.\n");
    
    add_item(({"sea","water"}), "It looks cold and blue.\n");

    add_exit(DAB_HARB + "bay4_2", "northwest", 0,6,1);
    add_exit(DAB_HARB + "bay4_3", "north", 0,6,1);
    add_exit(DAB_HARB + "bay4_4", "northeast", 0,6,1);
    add_exit(DAB_HARB + "bay5_2", "west", 0,6,1);
    add_exit(DAB_HARB + "bay5_4", "east", 0,6,1);
    add_exit(DAB_HARB + "bay6_3", "south", 0,6,1);
    add_exit(DAB_HARB + "bay6_4", "southeast", 0,6,1);

    set_up_herbs( ({ ONE_OF_LIST(OCEAN_HERBS),
                     ONE_OF_LIST(OCEAN_HERBS),
                     ONE_OF_LIST(OCEAN_HERBS),
                  }),
                  ({"water","here"}) , 
                   3 );

}
