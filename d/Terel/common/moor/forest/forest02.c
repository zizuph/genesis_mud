// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "/d/Terel/include/herb_arrs.h"
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

void
create_room()
{
    set_short("nearly midway up a dark mountain");
    set_long(
        "You are partway up a dark mountainside surrounded by grotesquely "+
        "gnarled oak trees.  The air is quite brisk and a chilling wind "+
        "carries a fine icy mist that clings to everything. Animal "+
        "footprints are visible in the thin crusty layer of ice on "+
        "the ground. A thick clump of briars is southeast, and a "+
        "small path zigzags up the mountain.\n"
    );

    add_item(({"briars", "clumps"}), 
        "The briars are rather thick and are covered with large sharp " +
	"looking barbs.\n"
    );

    add_item(({"footprints", "animal footprints"}),
        "You don't recogize the footprints as belonging to any animal you " +
        "know of.  Whatever left them had big feet with very large claws " +
	"though.\n"
    );    

    add_item(({"tree", "trees", "oak tree", "oak trees", "oaks"}), 
        "The oak trees are ancient and gnarled so grotesquely you wonder " +
        "if perhaps they were once diseased or cursed by some evil being.\n"
    );

    add_item("thicket", "It's an ordinary thicket.\n");

    add_item("ground", 
	"The ground has strange animal footprints pressed into the ice " +
	"and frost.\n"
    );
	
	set_up_herbs( ({ ONE_OF_LIST(FOREST_HERBS),
        ONE_OF_LIST(FROST_HERBS), ONE_OF_LIST(FOREST_HERBS)}),
      ({"trees","shrubbery","tree","shrubs","here"}) , random(3) );	
    
    add_prop(ROOM_I_INSIDE, 0);

    add_exit("thicket", "southeast");
    add_exit("forest03", "up");

}


