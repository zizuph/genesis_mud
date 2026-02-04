/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * bwalk_4.c
 *
 * Boardwalk, middle 
 * Goldberry July 14, 1999 
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>

#define DAB_HARB DABAAY_DIR + "harbor/"
#define CLIMB_MIN 20
#define FOUND_PILING "_found_piling"

inherit DAB_HARB + "port_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("On the boardwalk");
    set_long(
        "You are on a wooden boardwalk, east of the village "+
        "of Dabaay. Wooden piers stretch out to the north and south. "+
        "The boardwalk continues east out into the bay, and west "+
        "back into the village.\n");
    
    add_item(({"piers", "wooden piers"}), 
        "Well-built wooden piers on sturdy pilings. They will "+
        "withstand the worst of storms.\n");
    
    add_item(({"bay"}),	
        "You can see some fishing boats that have anchored in the "+
        "midst of the bay. Out towards the east and past some other "+
        "piers, the bay opens into the sea. There is a stone wall "+
        "stretching from the north shore into the bay.\n");
    
    add_item(({"sea"}), "It looks cold and blue.\n");

    add_item(({"pilings"}), 
        "Several stout and long wooden pilings support the piers.\n");

    add_item(({"wall","stone wall"}), 
        "The wall appears to be made from large stones, piled up "+
        "in a line from the north point to the center of the bay's "+
        "entrance. Every few moments a wave crashes over the wall.\n");
    
    add_exit(DAB_HARB + "npier_2", "north", 0);
    add_exit(DAB_HARB + "spier_2", "south", 0);
    add_exit(DAB_HARB + "bwalk_5", "east", 0);
    add_exit(DAB_HARB + "bwalk_3", "west", 0);
    add_exit(DAB_HARB + "un_bwalk3", "down", "@@ltest", 4,"@@see_down");

    add_prop(OBJ_S_SEARCH_FUN, "search_pilings");
    add_prop(OBJ_I_SEARCH_TIME, 1);


}

string 
search_pilings(object me, string arg)
{
    
    if((arg != "pilings") && (arg != "piling"))
    {
        return "";
    }
       if(!(TP->query_prop(FOUND_PILING)))
       {
          TP->add_prop(FOUND_PILING, 1);
          return "One particular piling has notches in it "+
                 "that make you think of a ladder.\n";
       }   
          return "Your search reveals nothing special.\n";
}

public int
ltest()
{
    if(!(TP->query_prop(FOUND_PILING)))
    {
        write("There is no obvious exit down.\n");
        return 1;
    }
   
    if(TP->query_skill(SS_CLIMB) < (CLIMB_MIN + random(10))) 
    {
        write("The piling looks too slippery!\n");
        return 1;
    }

    return 0;
}

public int
see_down()
{
    if(!(TP->query_prop(FOUND_PILING)))
       return 1;

    return 0;
}
