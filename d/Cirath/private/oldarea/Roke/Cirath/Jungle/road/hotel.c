inherit "/std/room";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
create_room()
{
  set_short("Small room in Kroll's Inn And Out.");
  set_long(break_string(
           "A nice room made totally in wood. This room works as "+
           "a hotel for tired travellers.\n",60));

/*  add_item("sign","The hotel is closed by the Gont board of health.\n");
*/
  add_item("sign","If you have a ticket you may type 'start here'\n"+
           "to start here the next time you enter the game.\n"+
           "You will quit automagically when you do so.\n");

  add_cmd_item("sign","read",
               "If you have a ticket you may type 'start here'\n"+
               "to start here the next time you enter the game.\n"+
               "Note that you will be logged out when you type\n"+
               "'start here'.\n");

  add_exit(JUNGLE+"road/inn","down",0);

  INSIDE;
}
init()
{
  ::init();

    add_action("start","start");
}
int start(string s)
{
  object ob;

  if(!(ob=present("krollsbille",TP)))
     {
       write("You don't have a ticket! You snort!\n");
       return 1;
     }
  NF("start where?\n");
  if(s!="here") return 0;

     ob->remove_object();

     TP->set_temp_start_location(JUNGLE+"road/hotel");

     write("You will start here the next time you enter the game.\n");
  TP->command("quit");
  return 1;  
}
