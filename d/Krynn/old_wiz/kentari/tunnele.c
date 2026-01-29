/*
   Knight Spur.

     tunnele.c
   ------------

   Coded ........: 12/96
   By ...........: Kentari

   Latest update : 12/96
   By ...........: Kentari
*/

#include "/d/Krynn/solamn/hctower/spur/local.h"
#include "/d/Krynn/common/defs.h"
inherit SPURRM;

#define HONORGUARD "/d/Krynn/kentari/mnstrs/honorguard.c"

object guardian;
int cloned;

create_spur_room()
{

   SHORT("Shadowed Tunnel");
   LONG("The tunnel is lit my torches that mysteriously burn, despite " +
	"the feeling you have that few people ever pass this way. " +
	"Shadows play on the walls and some seem so deep that you have " +
	"trouble distinguishing the width of this passage. Your " +
	"instincts also tell you that you are not alone, and you see " +
	"a twinkling outline of a platinum dragon within one of the " +
	"shadows. Ancient, yet sturdy stairs continue the way down.\n");
  
   INSIDE;
   LIGHT;
  
   AE(ROOM + "hall4", "west", 0);
   AE(ROOM + "museum", "down", 0);

   AI(({"torch","torches"}),
	"The torches shed a faint light, their flames dancing in the air, " +
	"making dark shadows on the walls. They seem a part of the tunnel.\n");
   AI(({"shadows","shadow","wall","walls","width","passage"}),
	"The walls of the passage are hidden deep in shadow, so much so " +
	"that you can't tell if there even _is_ a wall there, much less " +
	"what might be within.\n");
   AI(({"dragon","platinum dragon","outline","dragon outline","twinkling outline"}),
	"You could either 'study' or 'touch' this phenomenon, though you " +
	"feel hesistant about doing so.\n");
   AI(({"stairs","down","ancient stairs","sturdy stairs"}),
	"These stairs look old and worn, yet seem as sturdy and solid " + 
	"as the foundation of this Fortress.\n");
  
   reset_spur_room();
}

reset_spur_room()
{
   if (!guardian)
     (guardian = clone_object(HONORGUARD))->move_living(0,this_object());
}

void
init()
{
   ::init();
   ADD("do_look", "touch");
   ADD("do_look", "study");
}

nomask static int
do_look(string str)   
{
	if ((str=="dragon")||(str=="outline")||(str=="twinkling outline")||(str=="phenomenon"))
	   {
	   write("As you study the outline of the dragon, it suddenly " +
		"moves and you hear a voice from within the shadows.\n");
	   write("\n'Know that these sacred halls do not go unguarded. Only " +
		"those without treachery in their hearts may pass here " +
		"freely.'\n\n");
	   write("No matter how hard you look, you can't seem to find the " +
		"source of the ominous guardian.\n");
	   return 1;
	   }
	else write("To what do you refer?\n");
	return 1;
}
