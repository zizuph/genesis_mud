/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * un_bwalk1.c
 *
 * Under the boardwalk
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
    set_short("Under the boardwalk");
    set_long(
        "You are in the shallow waters underneath a wooden "+
        "boardwalk. Above you are the beams and planks that "+
        "that make up the walkway.\n");
    
    add_item("jetty",
        "A solid structure crafted from large stones.\n");

    add_item(({"stones","large stones"}),
        "Large, heavy-looking greay stones piled together "+
        "to create a jetty.\n");

    add_item("planks",
        "Rough-sawn and weather-beaten, the planks appear "+
        "to be less sturdy when looking at them from below.\n");

    add_item(({"pier", "wooden pier"}), 
        "It's a well-built wooden pier. It will withstand the " +
        "worst of storms.\n");

    add_item(({"boardwalk", "wooden boardwalk"}), 
        "It's a well-built wooden pier. It will withstand the " +
        "worst of storms.\n");
    
    add_item(({"bay"}),	
        "You can see some fishing boats that have anchored in the "+
        "midst of the bay. Out towards the east and past some other "+
        "piers, the bay opens into the sea. From this distance, you "+
        "can barely make out what appears to be a stone wall "+
        "stretching from the north shore into the bay.\n");
    
    add_item(({"sea","water"}), "It looks cold and blue.\n");
    add_item(({"sand","mud","muddy strip"}),
        "White to tan-coloured sand, wet from the seawater.\n");

    add_exit(DAB_HARB + "un_bwalk6", "west", 0,4,1);
    add_exit(DAB_HARB + "bay4_1", "east", 0,6,1);

    set_up_herbs( ({ ONE_OF_LIST(OCEAN_HERBS),
                     ONE_OF_LIST(OCEAN_HERBS),
                     ONE_OF_LIST(OCEAN_HERBS),
                  }),
                  ({"water","here"}) , 
                   3 );

}
