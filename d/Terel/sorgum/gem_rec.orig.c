inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define TP this_player()
#define NF(xx) notify_fail(xx)
#define BSN(xx) break_string(xx + "\n", 70)

init()
{
     ::init();
     add_action("do_recover", "recover");
}


void
create_room()
{

    set_short("Gem recovery room");
    set_long(BSN(
        "This is a small room where mortals come when they want to " +
	"recover their zodiac gems.  Use 'recover gem' and your zodiac " +
        "gem will be restored, _provided_ it was lost due to a bug and not " +
	"because of careless overuse."
    ));

    add_exit("/d/Terel/common/town/square3_1", "calathin", 0);
}

int
do_recover(string str)
{
    object gem;
    
    if (!strlen(str) || (str != "gem")) {
	NF("Recover what?  You want to 'recover gem' ??\n");
	return 0;
    }

    if ((TP->test_bit("Terel", QUEST_POR_GROUP,    QUEST_POR_BIT)   == 0) ||
	(TP->test_bit("Terel", QUEST_FIRE_GROUP,   QUEST_FIRE_BIT)  == 0) ||
	(TP->test_bit("Terel", QUEST_BAL_GROUP,    QUEST_BAL_BIT)   == 0) ||
	(TP->test_bit("Terel", QUEST_DEATH_GROUP,  QUEST_DEATH_BIT) == 0) ||
	(TP->test_bit("Terel", QUEST_MAZE_GROUP,   QUEST_MAZE_BIT)  == 0) ||
	(TP->test_bit("Terel", QUEST_CHI_GROUP,    QUEST_CHI_BIT)   == 0) ||
	(TP->test_bit("Terel", QUEST_ZOD_GROUP,    QUEST_ZOD_BIT)   == 0)) {
	NF("You haven't finished the zodiac quest!\n");
	return 0;
    }

    gem = clone_object("/d/Terel/zodiac/magic_gem");
    gem->move(TP);
    TP->catch_msg("Your zodiac gem has been restored.\n");
    return 1;
}
	
