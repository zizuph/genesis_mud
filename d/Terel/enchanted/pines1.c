/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * pines1.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "enchanted.h"

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    string *obj_list;

    obj_list = ({ });
    if (random(5) == 0)
	obj_list += ({ENCHANT_DIR + "obj/seed"});

    if (random(5) >= 1)
	obj_list += ({ENCHANT_DIR + "obj/rseed"});
    
    return obj_list;
    
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
   set_short("Pine Forest");
   set_long("Standing amidst gothic and silver laced pines, you " + 
	    "feel altogether diminutive. Winds war above you, passing " + 
	    "through the pines with whistles and howls. The floor of " + 
	    "the forest is coated with a layer of needles.\n");
   
   add_item("pines", "Strangely, they seem to watch your movements.\n");
   add_item(({"ground", "floor"}), "The ground is covered by needles.\n");
   add_item("needles",
	    "Under the coat of needles you find some very tiny mushrooms.\n");

   add_item(({"mushroom", "mushrooms"}),
      "The mushrooms seem to be too small to be picked and eaten.\n");

   add_cmd_item("mushroom", "pick", 
      "As you try to pick one mushroom it disolves into powder.\n");

   add_prop("_can_summon_the_forest", 1);

   add_exit(ENCHANT_DIR + "forest20", "northeast", 0);

   reset_room();
}
