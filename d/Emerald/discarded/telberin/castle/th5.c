/*
 * TH5.c
 * This is the actual throne room of Castle Telberin
 * - Alaron January 1997
 */

#include "default.h"
#include <macros.h>

inherit CASTLE_ROOM;

object king;
object queen;
object sen;

int stolen;

void reset_room();

int
query_stolen()
{
    return stolen;
}

void
set_stolen(int a)
{
    stolen = a;
}

void
create_room()
{
    ::create_room();
    set_short("The throne room of Castle Telberin");
    set_long("   This is the throne room of Castle Telberin. The comforts "+
	     "and extravagances arrayed before you are staggering. There "+
	     "are tables everywhere layered with foods of all kinds and "+
	     "origins. The thrones of the King and Queen of Telberin are "+
	     "raised slightly above the floor on a carpeted dais. Each "+
	     "throne is an elegantly carved, wooden chair with golden "+
	     "etchings upon it. Magnificent paintings and tapestries "+
	     "hang from carefully chosen locations throughout the room. You "+
	     "gather that the purpose of this room's decoration is to "+
	     "inspire awe and humility in those who visit it.\nA narrow "+
	     "hallway leads out of the throne room to the south through "+
	     "a red curtain.\n\n");
    
    add_item( ({"comforts", "extravagances", "food", "tables", "foods"}),
	     "The comforts and extravagances laid out in this room "+
	     "are nothing short of amazing. Hundreds of items of decoration "+
	     "are hanging in picturesque places. Some of those items "+
	     "could possibly support an entire family for a lifetime. The "+
	     "food laid out on the tables is amazing. It appears that there "+
	     "is food from nearly every corner of the world. All of the "+
	     "visitors to the throne are encouraged to take their fill, "+
	     "and no one is ever allowed to leave this room hungry. Every "+
	     "so often you will see a poor person slink into the room and "+
	     "be helped out by a guard assisting him with a few weeks "+
	     "worth of food.\n");

    add_item( ({"thrones", "wooden thrones", "wood thrones", "throne"}),
	     "The thrones of the King and Queen of Telberin are quite "+
	     "impressive. They are made of delicately carved wood, each "+
	     "piece with unique scrollwork and intricately carved "+
	     "designs. To accent the designs, shavings of gold are pressed "+
	     "into some of the curves and depressions created by the "+
	     "carvings.\n");

    add_item(({"dais", "carpted dais"}),
	     "The carpet upon the dais is a magnificent piece, most likely "+
	     "woven by one of the residents of Telberin. The borders of "+
	     "the carpet are simple, but beautiful designs, while the "+
	     "center of the carpet is an incredible depiction of a lion "+
	     "and a bear fighting one another.\n");

    add_item( ({"paintings", "tapestries", "curtains"}),
	     "The paintings and tapestries hung up on the walls all around "+
	     "the room are as impressive as the rest of the items "+
	     "here. Most of the paintings are depictions of members "+
	     "of the royal family, or what you guess is the royal "+
	     "family. Some of the paintings and all of the tapestries "+
	     "are skillfully created scenes of past victories or "+
	     "scenes from elven legend.\n");

    add_item( ({"curtain", "red curtain"}),
	     "It is a simple, red curtain which hangs over the open "+
	     "exit to the south. It is probably there to keep out the "+
	     "draft which continually causes the curtain to gently "+
	     "flap back and forth.\n");

   add_exit(CASTLE_DIR + "th4","north",0);
   add_exit(CASTLE_DIR + "th7","south","@@curtain");

   add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
   
   set_alarm(1.0, 0.0, reset_room);
}

void
reset_room()
{
   sen = present("seneschal");
   king = present("king");
   queen = present("queen");
   
   if(!(sen) || sen->query_name()=="ghost")
   {
       sen = clone_object(CASTLE_DIR + "npc/sen");
       sen->move_living("into a room", this_object());
   }
   else
   {
       sen = present("knight");
       if(!sen || sen->query_name() == "ghost")
       {
       }
   }
   if(!king)
   {
       king = clone_object(CASTLE_DIR + "npc/king");
       king->move_living("to his throne", this_object());
   }
   if(!queen)
   {
       queen = clone_object(CASTLE_DIR + "npc/queen");
       queen->move_living("to her throne", this_object());
   }

   if (!stolen)
   {
       stolen=1;
       sen->command("shout The queen's jewels have been stolen! The "+
		    "safe is empty and all we have is a big handprint "+
		    "from an Ogre!! Someone please help!");
   }
}

int
curtain()
{
    write("You step through the opening to the south, gently "+
	  "pushing the curtain aside ...\n\n");
    say(QCTNAME(TP)+ " steps through the opening to the south, "+
	"gently pushing the curtain aside.\n");
    return 0;
}
