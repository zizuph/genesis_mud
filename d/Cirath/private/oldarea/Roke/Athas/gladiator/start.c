inherit "/std/room";

#include "guild.h"

create_room()	{
  set_short("sleeping chamber");
  set_long("The din from the north is drowned out by the sounds of "+
           "snoring gladiators. Their sleeping arrangements range from "+
           "the floor to actual beds, but all are to tired to much care "+
           "what is beneath them.\n"+
           "You may <start here>.\n");
 
  add_cmd_item("gladiator", "wake", "You have a deathwish?\n");
 
  add_item("floor", "Its filthy, hard, and cold. Not all that unlike the "+
           "gladiators sleeping upon it.\n");
 
  add_item(({"bed", "beds"}), "Only the high ranking warriors get this "+
           "luxury. Victory isn't its own reward.\n");

    add_exit("/d/Cirath/athas/gladiator/room/gldboard","north",0);

}
init()
{
  ::init();

    add_action("start","start");
}

int start(string s)
{
   if(s =="here" && (IS_MEMBER(TP)))
     {
       TP->set_default_start_location(GLAD_DIR+"start");
       write("Ok.\n");
       return 1;
     }
  
	write("Either you are not a Gladiator, or you cannot type! "+
		"Try again, please.\n");
  return 1;
}

