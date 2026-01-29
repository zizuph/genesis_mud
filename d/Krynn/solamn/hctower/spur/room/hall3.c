// hall3.c
// grace aug 1994

#include "../local.h"                                                        
inherit "/d/Krynn/solamn/hctower/spur/room/std_hall.c"; 

void
create_spur_room()
{
   AE(ROOM + "hall4", "southeast", 0);
   clone_object(SOBJ + "portcullis2")->move(TO);    

    add_prop("_room_i_allow_steed", 1);

    make_the_room("The light behind the slits in the walls "+
       "seems to flicker like flame.");
}


