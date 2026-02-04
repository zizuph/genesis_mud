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
    set_short("forest");
    set_long(
	"You have left the path and ventured into the forest.  The trees " +
	"are rather thick here but they appear to thin out a bit to the " +
    "north.  Thick shrubbery and vegetation grow among the trees and " +
	"moss grows on the stones buried among the leaves and pine " +
	"needles of the forest floor.\n"
    );

	set_up_herbs( ({ ONE_OF_LIST(FOREST_HERBS),
        ONE_OF_LIST(FROST_HERBS), ONE_OF_LIST(FOREST_HERBS)}),
      ({"trees","shrubbery","tree","shrubs","here"}) , random(3) );
	  
    add_prop(ROOM_I_INSIDE, 0);

    add_exit("thicket", "west", 0);
    add_exit("clearing", "northwest", 0);
    add_exit("../hills/path02", "south", 0);        
}


