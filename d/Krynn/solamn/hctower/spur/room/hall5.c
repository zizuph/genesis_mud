// hall5.c
// grace aug 1994

inherit "/d/Krynn/solamn/hctower/spur/room/std_hall.c";
#include "../local.h"


void
create_spur_room()
{
   AE(ROOM + "hall6", "southeast", 0);
   clone_object(SOBJ + "portcullis3")->move(TO);    

    add_prop("_room_i_allow_steed", 1);

    make_the_room("It seems to be darker in here.");

}


