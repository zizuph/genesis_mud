// file name: ~Avenir/common/l3/sc1.c
// creator(s):
// revision history:
// purpose:
// note: Can contain piece of Source which can be obtained by 'exa hole'
//   I've taken the exa_fun away until the quest can be completed
//              -Iliyan, 1 May, 1995
// bug(s):
// to-do:

#include "l3_defs.h"
inherit L3_ROOM;
inherit SOURCE_CHECKER;
#include "/d/Avenir/common/dark/dark.h"

create_room()
{
    set_short("Dark guard room");
    set_long(
 "A small dark cavern off of the main tunnel. The air is filled with \n"+
 "moisture and it is difficult to breath. The walls and the floor "+
 "are covered with mud. In the gloomy " +
 "corners, moldy bunks rot away.\n"+
 "A foul stench emanates from a small hole in the floor.\n");

    add_item("bunks",
"These are foul-smelling, moldy, unkempt bunks of the guardians of "+
"the foul tunnels.\n");
   add_item("hole","@@exa_fun");

    add_exit("/d/Avenir/common/dark/l3/s3","southeast");

    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);

    add_prop(STATUES_IN_ROOM,2);
    set_alarm(0.5,0.0,"reset_room");
    can_contain_source=1;
}

string exa_fun()
{
    if(find_source(TP,0))
        return "Carefully examining the contents of the small hole "+
               "in the floor, you notice a small perfectly shaped glowing "+
               "crystal. You quickly grab it and clean it from the mud.\n";
    else
        return "The small hole in the floor is filled with mud, but "+
               "nothing else of interest.\n";
}
