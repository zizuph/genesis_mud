#include "../../../ctower.h"

inherit FIRESTD;
 
#include <macros.h>
 
int block();

int
ctower_reset()
{
    object npc;

    if (!(present("fire_elemental")))
    {
        setuid();
        seteuid(getuid());

        npc = clone_object(CTOWER_NPC + "fire_elemental");
        npc->move(this_object(), 1);
        tell_room(this_object(), "A column of flames erupts from " +
            "the ground, forming into a vaguely humanoid shape.\n");
   
        return 1;
    }
  
    return 0;
}
 
void
create_fire()
{
    add_exit("fire2", "north");
    add_exit("water5", "south");

    ctower_reset();
}


int
block()
{
    object npc;

    if (!(npc = present("fire_elemental")) ||
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
invoke_fire()
{
    return ctower_reset();
}
