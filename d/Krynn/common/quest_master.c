/* This file has nothing to do with the Questmaster in Solace!
 * This file maintains the state of most of the quests in Krynn.
 * This means specifically:
 *
 * - A registered quest can only be solved once per running of the clock.
 * - This means that once a quest has been solved, this file registers
 *   it and disallows giving out/solving the quest until the Krynn clock
 *   has been reset.
 * - In the questgiving function, you need to check if it's possible
 *   to do a certain quest.
 * - And in the exp-giving function, you need to do the same.
 *
 * You can use this file also for determining the current state of the
 * lands. Example: If quest A has been solved, then the road from X to Y
 * is free of dracs.
 * Note also that it may be necessary to check this file from the time flow
 * objects to determine the next actions to take.
 *
 * ~Aridor, 03/05/98
 * Revision history:
 *
 */

#include <macros.h>
#define LOGFILE "/d/Krynn/common/quest_master.log"

inherit "/d/Krynn/std/room";

private string* quest_list = ({});


void
create_room()
{
    restore_object(MASTER);
}

public nomask string*
query_all_solved_quests()
{
    return secure_var(quest_list);
}

public nomask int
query_quest_solved(string quest_id)
{
    return member_array(quest_id,quest_list) >= 0;
}


public nomask void
set_quest_solved(string quest_id)
{
    write_file(LOGFILE,ctime(time())[4..15] + "-" + ctime(time())[22..23] + " " +
           this_player()->query_name() +
           (this_player()->query_wiz_level() ? "(wiz!)" : "") +
           " set: " + quest_id + " (Prev obj: " + file_name(previous_object()) + ")\n");
    quest_list += ({ quest_id });
    save_object(MASTER);
}


public nomask void
reset_quests_solved()
{
    if (previous_object() != find_object("/d/Krynn/common/flow/clock"))
    {
    find_living("aridor")->catch_msg(this_player()->query_name() +
                     " tried to reset the quests.\n");
    write_file(LOGFILE,ctime(time())[4..15] + " " +
           this_player()->query_name() + " tried to reset the quests.\n");
    return;
    }

    quest_list = ({});
    save_object(MASTER);
}
