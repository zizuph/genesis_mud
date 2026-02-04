/* room2.c
mort 911004 remade 920812 Redhawk
Modified by Tomas adding herbs and terel std room Dec 1999

   Lilith Dec 2021/Jan 2022: 
      -moved out of the Sorgum Tomb dir
	  -updated cloning of swamp mobs
	  -updated descs and add_items
   
*/

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"
#include "../local.h"
inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";


/*
* Function name: create_room()
* Description  : Create the room.
* In this function, we declare everything that should be fixed
* when the room is started, and not changed in resets.
*/
void
create_room() {
   
   set_short("Snowy moor");
   set_long("This is the higher elevations of the moorland. There is more " +
      "snow on the ground here, and many more rocks. It seems more barren "+
	  "here, with the a brisk wind contributing to the feeling of desolation. "+
	  "A small group of trees have grown up in the east and a larger hill rises "+
	  "up in the north.\n");
   add_exit("moor4", "north",0);
   add_exit("moor2", "south",0);
   add_exit("trees", "east", 0);

    add_item(({"rocks", "megalithic rocks", "megaliths"}), 
        "There are megalithic rocks, some as small as a horse, others as big "+
        "as a house, scattered across the moors as if by a giant's hand.\n");
   add_item(({"heather", "ground", "moss"}),"The ground is covered in heather "+
       "and moss and standing water due to poor drainage.\n");
   add_item(("shrubs"),"Small shrubs litter the area.\n");
   add_item(({"trees","tree","small tree","small trees"}),
      "Several small trees dot the moorlands and line the roads.\n");
   add_item(({"hill","hills","moor", "moors"}),"Rolling hills covered in mist.\n");

    set_up_herbs( ({TER_HERB + "whitehorn"}),
                 ({"trees","small trees", "small tree"}), 
                     3 );
 
   add_npc(MOBDIR +"swamp_mob", 5);
   reset_room();
}

/*
* Function name:
* Description  :
*/

