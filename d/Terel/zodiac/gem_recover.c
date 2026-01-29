/*
    Modified: 3 May 2003, by Bleys
	- changed a sequence that was causing confusing messages

    Modified: 10 June 2003, by Bleys
	- The routine that checked whether a mortal had lost his
	    gem was mistakenly using a 1-index count (strlen())
	    in a 0-index context (extract()), which was always
	    a failure (because 'Bleys ' does not match 'Bleys').
	    Thus the gem was being restored and then immediately
	    destructed because of a similar, but functioning
	    check in the gem. This has been fixed now.
   Modified: 5 June 2008, by Lilith
	    Moves this room out of Sorgum's dir and into the zodiac dir

   Jan 2021, Lucius - Modernized and cleaned up.
*/
inherit "/std/room";
#include "/d/Terel/include/Terel.h"

#define LOST_GEM_LOG    "/d/Terel/open/lost_gem_log"
#define RECOVERED       "/d/Terel/open/recovered_gem_log"


void
create_room()
{
    set_short("Gem recovery room");
    set_long(
	"This is a small room where mortals come when they want to " +
	"recover their zodiac gems.  Use 'recover gem' and your zodiac " +
	"gem will be restored.\n");

    add_exit(CALATHIN_DIR + "square3_1", "calathin", 0);
}

public int
do_recover(string str)
{
    if (!strlen(str) || (str != "gem"))
    {
	NF("Recover what? You want to 'recover gem'??\n");
	return 0;
    }

    if ((TP->test_bit("Terel", QUEST_POR_GROUP,   QUEST_POR_BIT)   == 0) ||
        (TP->test_bit("Terel", QUEST_FIRE_GROUP,  QUEST_FIRE_BIT)  == 0) ||
        (TP->test_bit("Terel", QUEST_BAL_GROUP,   QUEST_BAL_BIT)   == 0) ||
        (TP->test_bit("Terel", QUEST_DEATH_GROUP, QUEST_DEATH_BIT) == 0) ||
        (TP->test_bit("Terel", QUEST_MAZE_GROUP,  QUEST_MAZE_BIT)  == 0) ||
        (TP->test_bit("Terel", QUEST_CHI_GROUP,   QUEST_CHI_BIT)   == 0) ||
        (TP->test_bit("Terel", QUEST_ZOD_GROUP,   QUEST_ZOD_BIT)   == 0))
    {
	write("You haven't finished the zodiac quest!\n");
	return 1;
    }

    /*  Recovery is no longer restricted
	if (file_size(LOST_GEM_LOG) > 0)
	{
            string *losers, who, player_name;
            int i, player_len;

	    player_name = TP->query_name();
	    player_len = strlen(player_name) - 1;
	    seteuid(getuid());
	    losers = explode(read_file(LOST_GEM_LOG), "\n");
	    for (i = 0; i < sizeof(losers); i++)
	    {
		if (extract(losers[i], 0, player_len) == player_name)
		{
		    write("\nYour gem has been destroyed through " +
			"incautious use, and cannot be recovered here.\n");

		    return 1;
		}
	    }
	}
    */

    write("Your zodiac gem has been restored.\n");
    // I've moved the write before giving the gem, because mortals
    //  were seeing "Your gem crumbles to dust." and then "Your
    //  zodiac gem has been restored." This should prove a more
    //  correct sequence of messages.
    //  - Bleys
    object gem = clone_object(ZODIAC_DIR + "magic_gem");
    gem->move(TP, 1);

    write_file(RECOVERED,
        TP->query_name() + " got a new gem. "+ctime(time())+".\n");

    return 1;
}

public void
init()
{
    ::init();
    add_action("do_recover", "recover");
}
