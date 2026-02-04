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
    set_short("forest path");
    set_long(
	"The narrow path continues northeast up an incline. " +
	"The air is quite brisk and a chilling wind carries " +
	"a fine icy mist that clings to everything.  There are patches " +
	"of snow here and there under the shade of the evergreens.\n"
    );


    add_item(({"mist", "icy mist"}), 
        "White and feathery it comes from the deep to its brothers " +
	"the clouds.\n"
    );
    
		
    set_up_herbs( ({ ONE_OF_LIST(FOREST_HERBS),
        ONE_OF_LIST(FROST_HERBS), ONE_OF_LIST(FOREST_HERBS)}),
      ({"trees","evergreens","tree","shrubs","here"}) , random(3) );
	  
    add_prop(ROOM_I_INSIDE, 0);

    add_exit("path01", "southwest", 0);
    add_exit("path03", "northeast", 0);
    add_exit("meadow01", "south", 0);
    add_exit("../forest/forest01", "north", 0);    
}
