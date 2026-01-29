/* highpass */

#include <filter_funs.h>
#include "climb.h"
#include "local.h"

inherit SHIRE_ROOM;
#define TROLLSH_DIR "/d/Shire/common/trollsh/"

void
create_shire_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    set_short("small cave");
    set_long("This is a small dim cave. Fortunately there is some light "+
	"coming inside through the small hole above your head so you "+
	"are able to see somehow.\n");

    add_item("hole", "You have entered this room through it. So maybe you "+
      "should use it again.\n");

    add_exit(MISTY_DIR+"r3", "down", "@@block_exit:" +
      file_name(this_object()) + "|"+MISTY_DIR+"r3@@");

    reset_shire_room();
}

int
block_exit(string room)
{
    if (present("_misty_goblin_", TO) && TP->check_seen(present("_misty_goblin_", TO)) &&
      (TP->query_prop(LIVE_O_LAST_ROOM) != find_object(room)))
    {
	write("The goblin guard stops you from passing.\n");
	say(QCTNAME(TP)+" was stopped from passing from the goblin guard.\n");
	return 1;
    }
    return 0;
}

void
reset_shire_room()
{
    object goblin1, goblin2, /* there are several goblins here    */
    armour, weapon, *treasure;
    int i, is_in_treasure;

    seteuid(getuid());

    if (!find_object(MISTY_DIR + "r3"))
	call_other(MISTY_DIR + "r3", "??");

    if(!present("_misty_goblin_"))
    {
	goblin1 = clone_object(GOBLIN_NPC_DIR +"goblin_high");
	goblin1->add_prop(LIVE_I_SEE_DARK, 1);
	goblin1->arm_me();
	goblin1->move_living("xxx", this_object());
	goblin2 = clone_object(GOBLIN_NPC_DIR +"goblin_med");
	goblin2->add_prop(LIVE_I_SEE_DARK, 1);
	goblin2->arm_me();
	goblin2->move_living("xxx", this_object());
	goblin1->team_join(goblin2); /* goblin1 will be the leader */

        object treasure = find_object(MISTY_DIR + "r3");
        if (!present("_filip_sword_", treasure)) {
            object weapon = clone_object(MISTY_WEP_DIR + "prisoner_sword");
            weapon->move(treasure, 1);
        }

        if (!present("_filip_armour_", treasure)) {
            object armour = clone_object(MISTY_ARM_DIR + "prisoner_cloak");
            armour->move(treasure, 1);
        }
    }
}

init()
{
    ::init();
    add_action("enter_hole", "enter");
}

int 
enter_hole(string hole)
{
    NF("Enter what?\n");
 
    if (hole !="hole" && hole != "the hole")
        return 0;

    if(!block_exit(MISTY_DIR+"r1"))
    {
        TP->catch_msg("You squeeze up through the hole.\n");
        say(QCTNAME(TP)+" squeezes up through the hole.\n");
        tell_room(MISTY_DIR+"r1",QCTNAME(TP)+" enters crawling from behind the tree.\n");
        TP->move_living("M",MISTY_DIR+"r1"); 
        return 1;
    }
    return 1;
}
