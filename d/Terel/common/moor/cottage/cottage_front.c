// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "../local.h"
#include "/d/Terel/include/herb_arrs.h"
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

void
create_room()
{
    set_short("outside cottage");
    set_long(
	"You are outside of a thatched cottage nestled into the surrounding " +
        "snowbanks.  Golden light is emanating from its windows and a " +
        "column of pale blue smoke is rising from the chimney as straight " +
        "as an arrow into the calm air. The smoke doesn't look natural.\n"
    );

    add_item(({"window", "windows"}),
    "There is a pleasant golden glow emanating from the windows, most " +
	"likely from a fire.  You can't see the inside of the cottage from " +
	"here.\n"
    );

    add_item(({"chimney"}), 
	"The chimney is made from red bricks.  The mortar between the bricks " +
	"looks like it has started to decay.  The chimney is in need of " +
	"a good tuck pointing.\n"
    );

    add_item(({"smoke", "blue smoke", "pale blue smoke"}), 
	"The pale blue smoke has a rather unnatural look about it.  What " +
	"could be burning in the fireplace to produce such odd looking " +
        "smoke?\n"
    );						      

    add_item(({"snow", "layer of snow", "snowbanks" }), 
    "A thin layer of snow covers the ground. The wind has piled "+
    "it up into snowbanks in some places.\n");

	set_up_herbs( ({ ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS) }),
                  ({"snowbank", "snow", "here"}) , 
                   3 );
	
    add_prop(ROOM_I_INSIDE, 0);

    add_exit("../hills/hill_base", "east", 0);
    add_exit("cottage_in", "enter", 0);
}
