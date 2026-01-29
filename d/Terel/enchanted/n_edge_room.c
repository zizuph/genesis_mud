/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * n_edge_room.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "/d/Terel/include/herb_arrs.h"
#include "/d/Terel/include/herbsearch.h"
#include "enchanted.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    string *herb_list;
    
    ::create_room();
    set_short("Northern Forest Edge");
    set_long("This is the northern edge of a large forest, dominated " + 
	     "mainly by tall conifers, though oaks and other deciduous " +
	     "trees also inhabit its depths.\n");
   
    add_item("tree", "They are tall and old, mostly conifers, but you " +
	     "can see some deciduous trees rising up from the canopy.\n");
    
    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    herb_list = query_herb_list();
    set_search_places(({"forest", "ground", "needles"}));    
    add_herb_file(one_of_list(ANY_HERBS));
    add_herb_file(one_of_list(FOREST_HERBS));
    add_herb_file(one_of_list(FOREST_HERBS));

//    add_herb_file(HERB_DIR + herb_list[random(sizeof(herb_list))]);
//    add_herb_file(HERB_DIR + herb_list[random(sizeof(herb_list))]);    
}

