/*
   High Clerist Tower - Spur.
   tunnel1.c
   -----

   Coded ........: February 1998
   By ...........: Kentari

   Latest update : February 1998
   By ...........: Kentari
   Reason .......: 
*/

#include "../local.h"
inherit SPURRM;

create_spur_room()
{
    SHORT("Shadowed Tunnel");
    LONG("The tunnel is lit by torches that mysteriously burn, despite " +
      "the feeling you have that few people ever pass this way. " +
      "Shadows play on the walls and some seem so deep that you have " +
      "trouble distinguishing the width of this passage.\n");

    INSIDE;
    LIGHT;
    
    clone_object(SOBJ + "l1d5b")->move(TO);
    AE(ROOM + "tunnel2","east",0);

    add_prop("_room_i_no_allow_steed", 1);

    AI(({"torch","torches"}),
      "The torches shed a faint light, their flames dancing in the air, " +
      "making dark shadows on the walls. They seem a part of the tunnel.\n");
    AI(({"shadows","shadow","wall","walls","width","passage"}),
      "The walls of the passage are hidden deep in shadow, so much so " +
      "that you can't tell if there even _is_ a wall there, much less " +
      "what might be within.\n");
 }
