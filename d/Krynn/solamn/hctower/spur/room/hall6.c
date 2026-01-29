// hall6.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_hall.c";
#include "../local.h"


void
create_spur_room()
{
   AE(ROOM + "hall5", "northwest", 0);
   clone_object(SOBJ + "steeldoor2")->move(TO);    

    add_prop("_room_i_allow_steed", 1);

    make_the_room("The tunnel continues to the northwest.");

}


