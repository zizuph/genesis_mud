#include "../defs.h"

inherit LIB_DIR + "rom";

create_rom() 
{
    set_short("Road in Bree");
    set_long(
	"You are walking on the Great Eastroad in the town of Bree. "+
	"It bends around the Bree-hill which is north-east of here. "+
	"Most of the houses of Bree are inhabited by men, and they "+
	"have settled on the lower slopes of the 'Hill' as it is called "+
	"by the locals. There is a low building to the east of here, with "+
    "a green sign hanging out.\n\n");
    add_item(({"sign","green sign"}),"@@sign_long");
    add_exit(BREE_DIR + "crossing", "north");
    add_exit(BREE_DIR + "townr2", "southeast");
/*    add_exit(STAND_DIR + "townr3", "southwest"); */
    add_exit(BREE_DIR + "shop", "east");
// holiday shop exit
//    add_exit(BREE_DIR + "hshop", "west");


    clone_object("/d/Genesis/obj/wizquest/mage_stone")->move(this_object());
}

init() {
    ::init();
    add_action("do_read","read");
}

do_read(str) {
    if (str == "sign" || str == "green sign");
    {
	write(sign_long());
	return 1;
    }
}

sign_long() {
    return "The sign reads: Tools & Supplies.\n";
}


