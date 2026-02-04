/*
 * herbroom.c
 * An example herbroom for Terel. Uses the Terel
 * herbsearch.c and herb_arrs.h
 *
 * Goldberry, November 1999
 */

#include "/d/Terel/include/Terel.h"

/* herb_arrs.h contains categorized arrays of
 * herbs. Refer to the beginning of herb_arrs.h
 * for definitions of the individual arrays.
 */
#include "/d/Terel/include/herb_arrs.h"  

inherit STDROOM;
inherit STDHSEARCH;  // "/d/Terel/std/herbsearch.c"

/* setting up a randomized function to grab
 * herbs out of the arrays
 */
#define ONE_OF_LIST(array) ((array)[random(sizeof(array))])

/* A locally defined herb array to select from
 * Use these for more specific groupings of herbs in
 * a room. Or for mixing conflicting categories in
 * a special circumstance
 */
#define EX_HERBS ({(TER_HERB + "sebre"),\
                   (TER_HERB + "moosho"),\
                   (GON_HERB + "suranie"),\
                 })


public void
create_room()
{
    ::create_room();
    set_short("Example herb room in Terel");
    set_long("An example herb room for Terel.\n"+
        "Use 'query_herbs' to see what herbs are loaded "+
        "up for this room.\n"+
        "Use 'query_search_places' to see where herbs can be "+
        "searched for in this room.\n");
    
/* setting up the herbs for the room */
/* set_up_herbs(string *hfiles, string *places , int time) */
/* '0' for places will result in the defaults: here and ground
 * being used as the search locations
 */
 
    set_up_herbs( ({ ONE_OF_LIST(EX_HERBS),      
                     ONE_OF_LIST(ANY_HERBS),
                     ONE_OF_LIST(FOREST_HERBS),
                     ONE_OF_LIST(MOUNT_HERBS),
                  }),
                  ({"foliage","brush","plants"}),
                  3 );

/* It is neccessary to add the places where one can search
 * for herbs. With the exception of "here" the player will
 * not be able to search the place for herbs, unless it 
 * exists in an add_item()
 */
    add_item("foliage","You can search this for herbs.\n");
    add_item("brush","You can search this for herbs.\n");
    add_item("plants","You can search this for herbs.\n");
}
