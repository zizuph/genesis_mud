#include "default.h"

inherit NOBLE_ROOM;

object *guard = allocate(4),
       captain;

void reset_room();

void
aid_the_queen(object enemy)
{
    if (captain)
    {
        captain->command("west");
        captain->command("shout For the Lady!");
    }
}

void
create_noble_room()
{
    set_short("In a hall of the Castle of the High-Lord");
    set_long("You find yourself in the middle of a hallway. "+
        "The walls around you are decorated with paintings. There "+
        "is a guarded exit to the west.\n");
        add_item("paintings","Surreal pictures of the Ancient Wars of "+
        "Legend.\n");
    INSIDE;

    add_item("carpet","The red carpet is soft and warm.\n");
    add_exit(NOBLE + "castle/c45", "north", 0, 0);
    add_exit(NOBLE + "castle/c49", "west", 0, 0);
    add_exit(NOBLE + "castle/c55", "south", 0, 0);

    reset_room();
}

void
reset_room()
{
    captain = clone_npcs(captain, NOBLE + "npc/castle_captain");
    guard = clone_npcs(guard, NOBLE + "npc/castle_guard");

    captain->team_join(guard[0]);
    captain->team_join(guard[1]);
    captain->team_join(guard[2]);
    captain->team_join(guard[3]);
}
