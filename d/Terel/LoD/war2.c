/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * war2.c
 *
 * A war room for the legion Redhawk 921103
 * Modified by Sorgum 941029
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "monster/warlord",
             LOD_DIR + "monster/war_officer"});
}

void
create_room()
{
    set_short("office of the Warlord of the Legion of Darkness");
    set_long("Everything in this room is over-sized. The desk is "+
             "huge, both in height and width. One would have to be "+
             "a giant to sit behind it. Instead of a chair there is "+
             "a stool that stands as tall as a human. The walls are " +
             "covered in large maps and drawings, some of them even "+
             "covering the paintings hanging there. There is an air "+
             "or urgency and rage in this place.\n");

    add_item(({"table"}), "It's a very big stone table with lots of " +
	     "maps on it.\n");

    add_item(({"stool"}), "It is made of wood and very tall. It "+
             "stands the height of an adult human.\n");
    add_item(({"map", "maps"}), 
	     "These maps are filled with marks and symbols in different " +
	     "colours, and you realise that these maps are very important " +
	     "papers for the legion commander.\n");

    add_cmd_item(({"map", "maps"}), "get", "@@attack");
    add_cmd_item(({"map", "maps"}), "take", "@@attack");

    add_item(({"painting", "paintings"}), 
	     "The paintings look well made, but it is hard to determine "+
             "what they depiect seeing as they are partially covered "+
             "by maps.\n");


    add_exit(LOD_DIR + "war1.c", "north", 0);
    reset_room();
}

string
attack()
{
    object mergula;
    object officer;

    mergula = present("mergula");
    if (mergula) {
	mergula->command("kill " + TP->query_real_name());
	return "You shouldn't mess with the legion's stuff.\n";
    } else if ((officer = present("war_officer"))) {
	officer->command("kill " + TP->query_real_name());
	return "You shouldn't mess with the legion's stuff.\n";
    }
    return "The maps cannot be taken.\n";
}
