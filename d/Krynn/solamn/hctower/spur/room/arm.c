// arm.c
// grace sept 1994

#include "../local.h"

inherit SPURRM;

object chest;

reset_spur_room()
{
  object key;
if(!chest)
   {
   chest=clone_object(SOBJ + "chest");
   chest->move(this_object());
   }
if(!present("key",chest))
  clone_object(SOBJ + "main_key")->move(chest,1);
} 

void
create_spur_room()
{

   SHORT("Back room");
   LONG("This room is very small.  The ceiling is low, and "+
      "the walls are close together.  There is a thick "+
      "accumulation of dust on the floor.\n");

   INSIDE;
   LIGHT;

   AE(ROOM + "armoire", "back", 0);

   AI(({"floor","stone floor"}),
      "It is covered in fine dust.  It probably hasn't been "+
      "cleaned in yers.\n");
   AI("ceiling", "It is oppressively low. You feel claustrophobic.\n");
   AI("dust", "It is quite fine and covers every exposed surface.\n");
   AI(({"wall", "walls"}), "The walls are smooth stone and a bare "+
     "two man-lengths apart.\n");

reset_spur_room();
}


