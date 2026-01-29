#include "defs.h"

inherit "/d/Shire/common/lib/rom";

create_rom()
{
    set_short("Road in Bree north of crossing.");
    set_long("You are walking on a road in the middle of Bree. "+
	     "To your northeast the breehill can be seen, that is "+
	     "where most of the inhabitants in Bree live, human "+
	     "as hobbits. You can see a huge and new building to your "+
	     "east and a small building to your west. There is a golden sign "+
	     "on the western building. The road continues north up "+
	     "towards the Bree-Hill, and south towards the Great Eastroad.\n");

    add_exit(STAND_DIR + "middle", "south", 0);
    add_exit(STAND_DIR + "hill1", "north", 0, 5);
    add_exit(STAND_DIR + "forge", "west", 0);
    add_exit(STAND_DIR + "bank", "east", 0);

    add_item(({"sign", "golden sign"}), "@@sign_long");

    add_item(({"breehill", "bree-hill", "hill"}),
	       "From here many small holes in the ground can be seen. "+
	       "Most likely it is the homes of the Hobbits living here. "+
	       "Some houses can also be spoted on the hill-side, and they "+
	       "are a bit bigger in size then the holes.\n");

    add_item(({"building"}),
	       "These buildings has recently been set up here, you can see "+
	       "that they are crafted in the finest elven traditions. \n");

    clone_object(BREE_DIR +"obj/trashcan")->move(TO);

}

init()
{

    ::init();
    add_action("do_read", "read");

}


do_read(str)
{
    if (str == "sign" || str == "golden sign");
    {
	write(sign_long());
	return 1;
    }
}

sign_long()
{
    return "The sign reads: Here the Blacksmith of Shire has his Forge.\n";
}
