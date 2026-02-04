// Modifications:
// Lilith, Jan 2022
//     Updated descs and exits for migration from Sorgum's dir to the 
//     Terel/common/moor dir.

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";


#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])


/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */
void
create_room() 
{

    set_short("Moor edge");
    set_long("These moors, ice coated and strewn with megalithic rocks, are " +
             "hauntingly beautiful. Moss and heather cover the ground, " +
             "as do many other shrubs. A small path leads northwest " +
             "off the moor up into the snow-covered hills that "+
			 "ring the area. Here, on the edge of the " +
             "moor, stands a black obelisk.\n");
    add_item(({"black obelisk", "obelisk"}), 
             "It stands about the height of an average human, and is cut "+
             "from dark obsidian worn smooth through countless storms. "+
             "Looking over the top of it, you can see a strange obelisk "+
			 "far to the northeast, up in the hills.\n");

    add_item(("heather"),"The ground is covered in it.\n");
    add_item(("shrubs"),"Small shrubs litter the area.\n");
    add_item(({"hill","hills"}),"Rolling hills covered in mist.\n");
    add_item(({"rocks", "megalithic rocks", "megaliths"}), 
        "There are megalithic rocks, some as small as a horse, others as big "+
        "as a house, scattered across the moors as if by a giant's hand.\n");
    add_exit("moor_path", "northwest",0);
    add_exit("moor2", "east",0);

    set_up_herbs( ({ ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                  }),
                  ({"shrubs", "heather", "hills", "here"}) , 
                     3 );
 
  reset_room();

}

/*
 * Function name:
 * Description  :
 */

