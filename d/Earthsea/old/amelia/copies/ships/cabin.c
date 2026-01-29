#pragma save_binary

inherit "/d/Genesis/ship/cabin";

#include "/d/Roke/common/defs.h"

void
create_cabin()
{
    set_short("A warm and cosy cabin inside the warship");
    set_long(BS("This is the admirals cabin. You can see that he is a very "+
		"wealthy man. Maybe he has won a lot of battles. There are "+
		"several nice paintings on the walls and in one corner of "+
		"the cabin there is a large desk with many maps. "+
		"You feel quite at home here and you could probably endure "+
		"any storm in this cabin.",76));

    add_item("desk", BS("Like most great desks this one is made out of finest"+
			" mahogany. It's quite big and is nailed to the "+
			"floor. Good thing to do, just in case a storm"+
			" comes up.",76));
    add_item(({"painting","paintings"}), BS("You recognize a copy of the "+
					    "famous Lona Misa. The rest of "+
					    "the pictures are paintings of "+
					    "different battles.",76));

    add_item(({"map", "maps"}), BS("The maps are nautical maps and "+
	     "there seem to be one or two doublets, some being riddled with "+
        "marks, lines, and notations while others seem brand new.",76));

    add_exit(SHIPS+"gontsparkle/deck", "up", 0);

    add_prop("_room_i_no_dig",1);
}
