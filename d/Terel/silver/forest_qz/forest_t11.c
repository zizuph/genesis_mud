/* File         : /d/Terel/silver/forest/forest_t11.c
 * Creator      : Tomas
 * Date         : August 2000         
 * Purpose      : forest file for Silver Forest.
 * Related Files: /d/Terel/silver/include/forest_base.c
 * Comments     : Basic Silver forest room.
 * Modifications: 
 */

#include "/d/Terel/include/Terel.h"
#include "../include/defs.h"

inherit INCLUDE + "forest_base";

public void
create_room()
{
    ::create_room();
    set_short_desc("camp");
    set_long("The massive Silver forest surrounds you. Its many " +
       "varieties of trees densely populate the area. Heavy snowfall " +
       "and the dense scrub brush makes it difficult for you to travel " +
       "swiftly through the forest. Some stumps of cut down trees can " +
	   "be seen around a tent in the middle of the stumps, this seem to " +
	   "be a campsite of some sort.\n");

	add_item("tent", "This is a regular ridge tent, it has a rectangular floor shape " +
             "that ranges between 20-30 feet in width and 10-15 feet in height. " +
	     "At each corner of the tent, a wooden pole is stuck to the ground " +
	     "with a guy rope bound to each of them to maintain the balance and " +
	     "structure of it all.\n");
	add_item(({"stump", "stumps"}),
        "Its about 15 of them and they surround the tent.\n");
  
    add_exit(FOREST_QZ + "forest_u11", "north",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s11", "south",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t12", "east",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u12", "northeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s12", "southeast",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_u10", "northwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_s10", "southwest",0,random(4),"@@exits");
    add_exit(FOREST_QZ + "forest_t10", "west",0,random(4),"@@exits");
	add_exit(FOREST_QZ + "tent", "tent", "@@tent_entrance", 1, 0);
	add_npc(NPC + "bandit", 4);
    reset_room();
}


int tent_entrance()
{
	if(sizeof(filter(all_inventory(TO), &->id("_silver_forest_bandit"))))
	{
		write("Bandits stop you from entering the tent!\n");
		return 1;
	}
	write("You enter the green ridge tent.\n");
	return 0;
}
