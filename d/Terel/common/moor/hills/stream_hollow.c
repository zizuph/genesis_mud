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
    set_short("stream hollow");
    set_long(
	"The sparkling stream flows through this sheltered hollow " +
	"composed of intermixed birch and cedar trees.  The white trunks " +
	"of the birch trees stand out in contrast to the darker cedars.\n"
    );

    add_item(({"cedars", "birches", "tree", "trees", "birch tree",
	       "cedar tree", "birch trees", "cedar trees"}), 
	     "The trees are exceptionally tall and healthy.\n");

    add_item("hollow", 
        "The sheltered hollow is so peaceful it has an almost hypnotic " +
	"effect on you.\n"
    );

    add_item("stream", 
        "The stream is very clear and cold.  The babbling of the stream " +
        "sounds almost like whispered speech.\n"
    );
    
    add_npc("/d/Terel/silver/monster/squirrel", 1);	

    add_prop(ROOM_I_INSIDE, 0);
	add_prop(OBJ_I_CONTAIN_WATER,1);
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);	
    add_prop("_live_i_can_fish", ({"freshwater"}));
	
	set_up_herbs( ({ ONE_OF_LIST(ANY_HERBS),
                    ONE_OF_LIST(RIVER_HERBS),
                    ONE_OF_LIST(RIVER_HERBS),
                 }),
                 ({"brook","gulley", "clay","stream"}) , 
                  3 );
				  
    add_exit("stream_falls", "east", 0);
	
    reset_room();
}


