/* 
Mort 911004
Updated by Tomas. Added Herbs then, changed to terel std room.
   
   Lilith Dec 2021/Jan 2022: moved out of the Sorgum Tomb dir
   
 */

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

/*
* Function name: create_room()
* Description  : Create the room.
* In this function, we declare everything that should be fixed
* when the room is started, and not changed in resets.
*/

void
create_room() 
{
   
   set_short("Icy moor");
   set_long("These wild moors are vast and seemingly barren at "+ 
      "first glance. Mists glide around these frost-covered hillocks "+
      "and water-logged soils. Giant rocks stand like sentinels "+
      "frozen in time and ice. Moss and heather cover the ground, " +
      "out-competing the shrubs. A small pool has formed here, "+
      "and can be entered to the northeast. Far north is a rocky "+
	  "hill, while south, through some trees, is a road. The overall "+
      "effect of this place is one of mysterious and haunting beauty.\n");

   add_exit("moor2", "north",0);
   add_exit("/d/Terel/common/road/road5", "south","@@check_troll");
   add_exit("pool", "northeast", 0);

   add_item(({"rocks", "megalithic rocks", "megaliths"}), 
       "There are megalithic rocks, some as small as a horse, others as big "+
       "as a house, scattered across the moors as if by a giant's hand.\n");
   add_item(({"heather", "ground", "moss"}),"The ground is covered in heather "+
       "and moss and standing water due to poor drainage.\n");
   add_item(("shrubs"),"Small shrubs litter the area.\n");
   add_item(({"trees","tree","small tree","small trees"}),
       "Several small trees dot the moorlands and line the roads.\n");
   add_item(({"hill","hills","moor", "moors"}), 
       "Rolling hills covered in mist.\n");
   
    set_up_herbs( ({TER_HERB + "whitehorn"}),
                 ({"trees","small trees", "small tree"}), 
                     3 );

  reset_room();

}


check_troll()
{
   if (this_player()->query_race_name()=="troll") 
   return 1;
}

