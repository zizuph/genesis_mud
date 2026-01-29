/* mainhall.c: Hallway guarded by Brutus. Serpine, 4-24-95 */
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("brutus", PSION_NPC+"brutus.c", 1, 1);
}

void
create_room()
{
    set_short("barren hallway");
    set_long("This hallway is cold and bare, with nothing to break the "+
             "monotony of angular stone. Unless of course you count the "+
             "dried blood of those who have dared face the Guardian of "+
             "the Gladiators. The sounds of combat echo through this "+
             "hallway from the west to the south, and the screams of "+
             "the arena audience echo from a tunnel running under the "+
             "stands to the north.\n");

    add_item(({"blood", "dried blood"}), "Unremarkable save in amount.\n");

    INSIDE

    add_exit(PSION_ROOM+"stairwy1.c", "west", "@@west_block@@", 1);
    add_exit(PSION_ROOM+"entrance.c", "south", 0, 1);
    reset_room();
}

int
west_block()
{
  object guard = present ("brutus", TO);
  if(objectp(guard))
  {
    if((!IS_MEMBER(TP))&&(!IS_WIZ(TP)))
    {
      TP->catch_msg(QCTNAME(guard)+" shoves you back.\n");
      return 1;
    }    
    TP->catch_msg(QCTNAME(guard)+" salutes with his axe as you pass.\n");
  }
  return 0;
}
