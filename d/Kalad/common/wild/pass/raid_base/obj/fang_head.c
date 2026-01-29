#pragma strict_types
#pragma no_inherit

inherit "/std/leftover";

#include "../defs.h"


public void
create_leftover()
{
   ::create_leftover();
   add_prop(RAID_GOBLIN_LEFTOVER, 1);
   leftover_init("head", "goblin");
}
