#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"

void
create_room()
{
    set_short("middle of staircase");
    set_long("You stand upon a stone staircase that spirals both upwards "+
             "and down. The loud din of talking to the south and sparring "+
             "to the east, not to mention the howl of the wind from below, "+
             "echoes in a strange and unsettling way off the carvings on "+
             "the wall.\n");

    add_item(({"carvings", "carving", "wall", "walls"}), "Disturbing "+
             "images of faces contorted in pain and death adorn the wall. "+
             "Most of them are crude, as they are carved by gladiators in "+
             "honor of worthy opponents who fell before them in battle.\n");
    add_item(({"staircase", "stone staircase"}), "An ominous sense of "+
             "implied violence seems to radiate from the upper floor.\n");

    INSIDE

    add_exit(PSION_ROOM+"stairwy1.c", "down", 0, 1);
    add_exit(PSION_ROOM+"stairwy3.c", "up", 0, 1);
/*
    add_exit(PSION_ROOM+"training.c", "east", "@@check_leave@@", 1);
    add_exit(PSION_ROOM+"gldboard.c", "south", "@@check_leave2@@", 1);
*/
    add_exit(PSION_ROOM+"training.c", "east", 0, 1);
    add_exit(PSION_ROOM+"gldboard.c", "south", 0, 1);
}
int
check_leave()
{
  if ((IS_MEMBER(TP)) && (!TEST_GBIT(TP, PSION_MEMBER)) && (!IS_WIZ(TP)))
  {
      write("You must update your membership in the join room "+
            "before you will be allowed to train again.\n");
      return 1;
  }
    return 0;
}
int
check_leave2()
{
    if((!IS_MEMBER(TP))&&(!IS_WIZ(TP)))
    {
        TP->catch_msg("You mind explodes with pain: 'I am Kalak!' "+
            "a voice says. 'You will not invade the sanctum of the "+
            "gladiators.'\n");
        return 1;
    }
    return 0;
}