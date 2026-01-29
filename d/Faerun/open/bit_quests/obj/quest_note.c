/* 
 * This is an example of a quest note given to players that involve 
 * quests using bits.
 * Based on the tour note from Pelargir, originally coded by Elessar, May 92.
 * -- Finwe, June 2017
 */

inherit "/std/object";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

int     quest_no,
        quest_done;
string  task,
        player_name,
       *cnames = ({});

void
create_object()
{
    set_name("note");
    add_name("example_quest_note");
    set_short("@@short_desc@@");
    set_pshort("quest notes");
    set_long("@@long_desc@@");
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 20);
}

void
set_quest_no(int i)
{
    quest_no = i;
}

int
query_quest_no()
{
    return quest_no;
}

void
set_quest_done()
{
    quest_done = 1;
}

void
set_player_name(string str)
{
    player_name = str;
}

string
query_player_name()
{
    return player_name;
}

int
query_quest_done()
{
    return quest_done;
}

void
set_task(string s)
{
    task = s;
}

string
query_task()
{
    return task;
}

string
short_desc()
{
    if (quest_done)
        return "quest note (solved)";
    return "quest note (unsolved)";
}

string
long_desc()
{
    string ld = "This is a quest note. It is proof of the quest assigned " +
        "to you. ";

    ld += "The task is this:\n\n" + task;

    if (quest_done)
        ld += "\nThe task is solved. Return to the quest master for your " +
        "reward.\n";
    else
        ld += "\nThe task is not solved yet.\n";

    return ld;
}
