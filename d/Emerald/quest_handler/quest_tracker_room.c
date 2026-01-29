/**
* This room is a control object that returns various quest
* information about a player and Emerald quests.
* Louie  2006
*/

#pragma strict_types

inherit "/std/room.c";
#include "/d/Emerald/quest_handler/quest_handler.h"

//proto
int query_completed_quests_emerald();

void
create_room()
{
    set_short("quest tracking room");

    set_long("This room is just a quest tracking room.  "+
        "\n");
    
}


void
init()
{
    ::init();
    add_action(query_completed_quests_emerald, "quests");
}

int query_completed_quests_emerald() {
    object tp = this_player();
    //Get active quest names
    mixed *names = QH_QUERY_QUEST_NAMES(1);
    int total = 0, completed = 0, i;
    if (pointerp(names))
        total = sizeof(names);
 
    i = total;
    while (i--) {
        if (QH_QUERY_QUEST_COMPLETED(tp, names[i]))
            completed++;
    }

    write("You have completed "+completed+" of "+total+" Emerald quests.\n");
    return 1;
}