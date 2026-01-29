/*
   Knight Spur.

     tunnel3.c
   ------------

   Coded ........: 12/96
   By ...........: Kentari

   Latest update : 2/98
   By ...........: Kentari
   Reason .......: Added Doors to Entrance
*/

#include "../local.h"
#include "/d/Krynn/common/defs.h"
inherit SPURRM;

object kn1, kn2;
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

    AE(ROOM + "tunnel2", "west", 0);
    AE(ROOM + "museum", "down", "@@check_align");

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

int
check_align()
{
    if (!P(kn1, TO) && !P(kn2, TO))
    {
	return 0;
    }

    if (TP->query_alignment() > -100)
    {
	write("The knights on duty here allow you to pass, apparently "+
	  "trusting you.\n");
	say("The knights on duty here allow "+QTNAME(TP)+" to pass, "+
	  "apparently trusting "+OBJECTIVE(TP)+".\n");
	return 0;
    }

    if(!CAN_SEE(kn1, TP) && !CAN_SEE(kn2, TP))
    {
	return 0;
    }

    write("The knights on duty here stop you, and refuse to let "+
      "you continue downwards.\n");
    say("The knights on duty here stop "+QTNAME(TP)+" as "+
      PRONOUN(TP)+" tries to go down.\n");
    return 1;
}

reset_spur_room()
{
    if(!kn1)
    {
	kn1 = clone_object(SNPC + "guard");
	kn1->move(TO);
    }
    if(!kn2)
    {
	kn2 = clone_object(SNPC + "guard");
	kn2->move(TO);
    }
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
	  "source of the ominous voice.\n");
	return 1;
    }
    else write("To what do you refer?\n");
    return 1;
}
