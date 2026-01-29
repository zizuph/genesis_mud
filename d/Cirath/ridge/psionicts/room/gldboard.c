/* gldboard.c: Gladiator board room: Serpine, 4-24-95. */
// Edited a bit to take advantage of my revised board: Shiva, 8-7-95
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#include <macros.h>

object vote_bucket;

static void
create_board()
{
    object board;
    /*
        if ((board = clone_object(GLAD_ROOM + "shiva_board")))
    */
    if ((board = clone_object("/std/board")))
    {
        board->set_board_name(PSION_LOG+"board");
        board->set_num_notes(50);
        board->set_silent(1);
        board->set_err_log(PSION_LOG+"glad_board_err");
        board->set_show_lvl(0);
        board->set_lock_lvl(0);
        board->set_lock_access(VBFC_ME("may_lock"));
        board->set_unlock_access(VBFC_ME("may_lock"));
        board->move(TO);
    }
    return 0;
}

void
reset_room()
{
    if (!present("board", TO))
        create_board();
    if (QUERY_OVERSEER) return;
    if (!vote_bucket)
    {
        vote_bucket=clone_object(PSION_LOG+"gladvote.c");
        vote_bucket->move(TO);
    }

    vote_bucket->check_over_time();
}

create_room()
{
    object board;
    set_short("meeting hall");
    set_long("This is the the heart of the Guild of Gladiators, where "+
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

    add_exit(PSION_ROOM + "stairwy2.c", "north", 0, 1);
    add_exit(PSION_ROOM + "meditate.c", "east", 0, 1);
    add_exit(PSION_ROOM + "startspt.c", "south", 0, 1);
    add_exit(PSION_ROOM + "gldchest.c", "west", "@@templar_message", 1);

    reset_room();
}

int may_lock()
{
    int i;
    i = (QUERY_COUN_MEMB(this_player()->query_real_name()) < 0 &&
      !this_player()->query_wiz_level());
    find_player("luther")->catch_msg(i + "\n");
    return i;
}

int
templar_message()
{
    string name = TP->query_real_name();

    TP->catch_msg("A Templar hidden within an alcove glares at a "
      +"parchment as you stride past.\n");

    if (CHECK_PUNISHMENT(EXPEL, name)) 
    {
        TP->catch_msg("Suddenly the Templar growls softly and a "
          +"deafening voice in your head says 'FOOL! You "
          +"dare try to march past me? Know that the Overseers "
          +"expelled you. You are a Gladiator in name only. "
          +"The chest is not for you use any longer.\n");
        return 1;
    }

    if((!IS_MEMBER(TP))&&(!IS_WIZ(TP)))
    {
        TP->catch_msg("Suddenly the Templar growls softly and a "
          +"voice inside your head says: 'You are not "
          +"a gladiator, you may not enter that room. "
          +"Unless of course, you are volunteering for "
          +"service...'\n");
        return 1;
    }


    return 0;
}
