/*
   High Clerist Tower - Spur
   hall4.c
   -----

   Coded ........: August 1994
   By ...........: Grace

   Latest update : January 1998
   By ...........: Kentari
   Reason .......: Added entrance to Museum Tunnel
*/

inherit "/d/Krynn/solamn/hctower/spur/room/std_hall.c";
#include "../local.h"
#include <ss_types.h>

void
create_spur_room()
{
    clone_object(SOBJ + "l1d5a")->move(TO);
    AE(ROOM + "hall3", "northwest", 0);
    AE(ROOM + "stairs", "up", 0); 
    clone_object(SOBJ + "portculliso3")->move(TO);    

    add_prop("_room_i_allow_steed", 1);

    make_the_room("In the dimness you can just see a flight of "+
      "stairs leading up.");
}

init()
{
    ::init();
}
