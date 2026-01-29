/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * forest_room.c
 *
 * A generic enchanted forest room.  All the enchanted forest rooms
 * should inherit this file.
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"
inherit STDROOM;

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

    set_short("Forest");
    set_long("You are within the depths of a great forest. An air of\n"
	     + "enchantment lingers here, a stirring from within the trees\n"
	     + "themselves. The trees are tall and old, their canopy thick\n"
	     + "and impenetrable. The wind howls through the heights of the\n"
	     + "trees, whistling needles provide an eerie feeling.\n");
   
    add_item("trees", "Countless numbers of trees, many ancient, some\n"
	     + "only young saplings awaiting their chance to grow. The trees\n"
	     + "struggle amongst each other for dominance, some never make it.\n");
    
    add_item("canopy",
	     "It is the thick roof of the forest, formed by countless\n"
	     + "branches, leaves and needles. Very little light enters\n"
	     + "down to the forest floor.\n");
    
    add_item("needles",
	     "These are the leaves of the conifers, many of age have\n"
	     + "fallen and formed a carpet upon the forest floor.\n");
    
    add_item(({"carpet", "floor"}),
	     "Layered in a soft blanket of pine needles,\n"
	     + "the forest floor seems almost carpeted.\n");
    
    OUTSIDE;

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

