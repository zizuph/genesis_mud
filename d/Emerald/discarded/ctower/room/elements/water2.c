#include "../../ctower.h"

inherit WATERSTD;
 
#include <macros.h>
 
int block();

int
ctower_reset()
{
    object npc;

    if (!(present("water_elemental")))
    {
        setuid();
        seteuid(getuid());

        npc = clone_object(CTOWER_NPC + "water_elemental");
        npc->move(this_object(), 1);
        tell_room(this_object(), "The water begins to swirl in a " +
            "mirky vortex which takes on a vaguely humanoid shape.\n");
   
        return 1;
    }
  
    return 0;
}
 
void
create_water()
{
    add_exit(CTOWER_ROOM_ELEM + "water3", "southwest", block);
    add_exit(CTOWER_ROOM_ELEM + "water4", "southeast", block);
    add_exit(CTOWER_ROOM_ELEM + "earth2", "north");

    ctower_reset();
}

int
block()
{
    object npc;

    if (!(npc = present("water_elemental")) ||
        this_player()->query_wiz_level())
    {
        return 0;
    }
  
    write(npc->query_The_name(this_player()) + " blocks your way!\n");
    say(QCTNAME(this_player()) + " attempts to leave, but the " +
        QTNAME(npc) + " blocks " + this_player()->query_possessive() +
        " way.\n");
    return 1;
}

int
invoke_water()
{
    return ctower_reset();
}
