/* gldboard: Gladiator board room: Serpine, 4-24-95. */
// Edited a bit to take advantage of my revised board: Shiva, 8-7-95
#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <macros.h>

private object board;
private object barrel;
private object vote_bucket;

void
configure_board()
{
    board->set_board_name(GLAD_LOG + "board");
    board->set_num_notes(50);
    board->set_silent(1);
    board->set_err_log(GLAD_LOG + "glad_board_err");
    board->set_show_lvl(0);
}

void
reset_room()
{
    CLONE(barrel, "/d/Raumdor/common/obj/tbarrel");
    CLONE(board, "/std/board");

    configure_board();

    if(MANAGER->query_overseer_by_position(POS_HIGH))
    {
        if(vote_bucket)
        {
            vote_bucket->remove_object();
        }

        return;
    }

    CLONE(vote_bucket, GLAD_DIR + "gladvote");
    vote_bucket->check_over_time();
}

void
create_room()
{
    set_short("meeting hall");
    set_long("This is the heart of the Guild of Gladiators, where " +
      "they meet to talk of battles past and prepare for those yet "+
      "to come. Crude artwork brightens the otherwise grim stone "+
      "walls and passing warriors produce a great deal of "+
      "noise as they go about their business. Many of them head "+
      "north towards the sound of battle, though a few who are "+
      "more calm head east or south.\n");

    add_item(({"artwork", "crude artwork"}), "No matter how often slaves "+
      "are forced to clean it the gladiators scrawl more on the "+
      "walls. Even in this they are a stubborn breed.\n");
    add_item(({"warrior", "warriors", "gladiator", "gladiators"}), "Most "+
      "of them don't seem interested in talking to you.\n");

    add_exit(GLAD_ROOM + "stairwy2", "north", 0, 1);
    add_exit(GLAD_ROOM + "meditate", "east", 0, 1);
    add_exit(GLAD_ROOM + "startspt", "south", 0, 1);
    add_exit(GLAD_ROOM + "gldchest", "west", "@@templar_message", 1);

    reset_room();
}

int
templar_message()
{
    string name = TP->query_real_name();

    TP->catch_tell("A Templar hidden within an alcove glares at a "
      +"parchment as you stride past.\n");

    if (CHECK_PUNISHMENT(name, PUN_EXPEL)) 
    {
	TP->catch_tell("Suddenly the Templar growls softly and a "
	  +"deafening voice in your head says 'FOOL! You "
	  +"dare try to march past me? Know that the Overseers "
	  +"expelled you. You are a Gladiator in name only. "
	  +"The chest is not for you use any longer.\n");
	return 1;
    }

    if((!IS_MEMBER(TP)) && (!IS_WIZ(TP)))
    {
	TP->catch_tell("Suddenly the Templar growls softly and a "
	  +"voice inside your head says: 'You are not "
	  +"a gladiator, you may not enter that room. "
	  +"Unless of course, you are volunteering for "
	  +"service...'\n");
	return 1;
    }


    return 0;
}
