// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, added add_items, etc.
// This is the room where the flower pot for the 
// cracked safe quest is cloned. 

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/include/herb_arrs.h"

inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";
#include "../local.h"

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])


void
create_room()
{
    set_short("cottage garden");
    set_long("Here, next to the sloppy vegetable garden, are the remains "+
        "of a flower garden. There are various dead plants and old rose "+
        "bushes lying half-covered in snow, as well as lots of dried, "+
        "straw-like weeds.\n");
 
    add_item(({"plants", "dead plants", "bushes", "weeds", "rose bushes"}),
        "They are all dead or dormant under the snow.\n");
    add_item(({"snow", "layer of snow"}), "A thin layer of snow covers "+
        "the ground.\n");
    add_item(({"flower" , "flowers", "rose", "roses" }), 
        "They are all dead or dormant for the winter.\n");	
		
    add_prop(ROOM_I_INSIDE, 0);

    seteuid(getuid(TO));
	
	set_up_herbs( ({ ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS),
                     ONE_OF_LIST(FROST_HERBS) }),
                  ({"plants", "weeds", "bushes", "snow", "here"}) , 
                   3 );
				   
    // This is for the safe-cracking quest.
	// Cloning 2 so there is a second chance if the wrong
	// ingredients are mixed together.
    add_object(OBJDIR + "flower_pot", 2);

    add_exit("cottage_garden", "east", 0);
}


