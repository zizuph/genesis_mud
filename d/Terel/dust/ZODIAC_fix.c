/*
 * BIT CLEARER: A REALLY UGLY HACK TO FIX A PROBLEM WITH THE ZODIAC QUEST
 * Here's the problem: The move to the new machine (July 1, 1993, when we
 * moved to a DEC Alpha named hama12.cs.chalmers.se) seems to have changed
 * the random() efun, so that given a particular range and seed it no longer
 * returns the same random number it did before the move. Since the ramdom
 * order of the buttons to be pressed in the ZODIAC quest uses the player's
 * name (converted to a number) as a seed, this will mess up any players
 * who have partially completed the quest. So..this machine, when they
 * pull a level, will clear all the quest bits in the zodiac quest (Terel
 * group 0, bits 0, 2, 13, 1, 18, and 3) and log the player's name. The
 * machine will not clear the bits of anyone with bit 17 (the ZODIAC) set
 * nor anybody whose name is in the log file. This is going to give an unfair
 * advantage to those who have partially completed the quest since those people
 * will be able to get experience twice for the parts they've completed. No way to 
 * help this as far as I can tell.
 * 
 * --Cedric
 */
 
/*
 * Patched this on instructions of Mercade. No need to remove those
 * bits, since the parts of the quest can be solved multiple times.
 * Uhm, removing those bits doesn't add anything to the solution of the
 * problem regarding the random generator.
 *
 * Undefine TRICKY_PATCH to get the old machine. :-)
 *
 * Tricky, with the help of Mercade
 */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define TP this_player
#define LOG_FILE "/d/Terel/dust/LOG--save"
#define BS(xx) break_string(xx,75)

#define TRICKY_PATCH

void
create_object()
{
#ifdef TRICKY_PATCH
    set_name("notice");
    set_adj("important-looking");
    set_long("Due to a change in the fabric of space the hints you have "
	+ "received for the solution of the zodiac quest have changed. "
	+ "This means that hints you received before July 1st, 1993, have lost "
	+ "their value. You are STRONGLY advised to check on all hints you "
	+ "received before july 1st before you try anything in this room.\n"
	+ "\n"
	+ "Mercade.\n");
#else
    set_name("machine");
    add_adj("complex");
    add_adj("important-looking");
    set_long(BS("This machine was installed recently by Lord Cedric to fix a bug "
    + "in the door. If you have gathered any of the quest hints before July 1, "
    + "1993, you'll need to pull the lever on this machine and do ALL the "
    + "quests again--the hints have changed. You can only pull the lever once, "
    + "ever, and if you have passed through this door before you cannot pull "
    + "the lever even that one time. Sorry for the inconvenience, but the bug "
    + "is a feature of the new machine we're running on and can't be worked "
    + "around. Note that you should not use the machine unless you have "
    + "acquired any of the hints previous to the above date! Using the machine "
    + "can scramble your hints and will likely cause your death if you don't "
    + "follow this rule!\n"));
#endif
    add_prop(OBJ_I_NO_GET, 1);
}

#ifndef TRICKY_PATCH
void
init()
{
    ::init();
    add_action("do_pull", "pull");
}

int
do_pull(string str)
{
    string *names;
    
    if (str != "lever")
	return 0;
    if (TP()->test_bit("Terel", QUEST_ZOD_GROUP, QUEST_ZOD_BIT))
    {
	notify_fail(BS("You fool! You've passed through this door! Leave now, and "
	+ "consider yourself lucky to be alive...\n"));
	return 0;
    }
    names = explode(read_file(LOG_FILE)+"\n", "\n");
    if (member_array(TP()->query_real_name(), names) != -1)
    {
	notify_fail(BS("You fool! You've pulled the lever before! Leave now, and "
	+ "consider yourself lucky to be alive...\n"));
	return 0;
    }
    TP()->clear_bit(QUEST_FIRE_GROUP, QUEST_FIRE_BIT);
    TP()->clear_bit(QUEST_BAL_GROUP, QUEST_BAL_BIT);
    TP()->clear_bit(QUEST_DEATH_GROUP, QUEST_DEATH_BIT);
    TP()->clear_bit(QUEST_MAZE_GROUP, QUEST_MAZE_BIT);
    TP()->clear_bit(QUEST_POR_GROUP, QUEST_POR_BIT);
    TP()->clear_bit(QUEST_CHI_GROUP, QUEST_CHI_BIT);
    TP()->catch_msg("The machine hums and whirs. Suddenly you can't remember "
    + "ANY of the hints you've gathered! You realize that you'd better check "
    + "ALL of them again before you attempt anything in this room.\n");
    write_file(LOG_FILE, TP()->query_real_name()+"\n");
    return 1;
}
#endif
