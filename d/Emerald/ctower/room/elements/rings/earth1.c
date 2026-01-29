#include "../../../ctower.h"

inherit EARTHSTD;

#include <macros.h>
 
int block();

int
ctower_reset()
{
    object npc;

    if (!(present("earth_elemental")))
    {
        setuid();
        seteuid(getuid());

        npc = clone_object(CTOWER_NPC + "earth_elemental");
        npc->move(this_object(), 1);
        tell_room(this_object(), "The ground begins to rumble, and " +
            "a pile of rock and dirt is thrust upwards, taking on " +
            "a vaguely humanoid shape.\n");
   
        return 1;
    }
  
    return 0;
}
 
void
create_earth()
{
    add_exit("earth2", "northwest", block);
    add_exit("earth12", "northeast", block);
    add_exit("air9", "south");

    ctower_reset();
}

int
block()
{
    object npc;

    if (!(npc = present("earth_elemental")) ||
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
invoke_earth()
{
    return ctower_reset();
}
