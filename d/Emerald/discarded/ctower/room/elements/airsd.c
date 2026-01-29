#include "../../ctower.h"

inherit AIRSTD;

#include <macros.h>
 
int block();

int
ctower_reset()
{
    object npc;

    if (!(present("air_elemental")))
    {
        setuid();
        seteuid(getuid());

        npc = clone_object(CTOWER_NPC + "air_elemental");
        npc->move(this_object(), 1);
        tell_room(this_object(), "The winds being to churn violently, " +
            "picking up dust and debris, which seem to take on a " +
            "vaguely humanoid shape.\n");
   
        return 1;
    }
  
    return 0;
}
 
void
create_air()
{
    add_item(({"stair", "stairs", "stairway"}),  "This "+
	"stairway appears to be quite sturdy even though"+
	" there doesn't seem to be any visible support.\n" );
  
    add_exit("trialsu", "down");
    add_exit("air2", "southwest", block);
    add_exit("air3", "southeast", block);
  
    ctower_reset();
}

int
block()
{
    object npc;

    if (!(npc = present("air_elemental")) || this_player()->query_wiz_level())
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
invoke_air()
{
    return ctower_reset();
}
