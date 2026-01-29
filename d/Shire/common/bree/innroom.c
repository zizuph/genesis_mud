/*
 *  The common sleeping room of the Old Guesthouse
 *  
 *  copied from the hotel room in Re Albi 
 *
 *  created by unknown 
 *  modified for The Old Guesthouse by Olorin on 6-jan-93
* Now modified to be used as the inn in Mithlond
* Quark, 24, aug -94
* Err, no, this is the Prancing Pony's... Dunstable 9/94
*/

inherit "d/Shire/room.c";
/*
 * Sets flag in players from calling dragons into ME.
 * Disabled by request of Admin, June 2001
#include "/d/Gondor/common/lib/gs_include.c"
*/
#include "/sys/macros.h"
#include "/d/Shire/common/defs.h"

create_room()
{
   set_short("A room in the Prancing Pony");
  set_long(
   "You have entered a dim room on the ground floor of "+
    "Bree's finest (and only) lodgings. There are several "+
    "beds lying about unused- you feel sure no one will mind "+
    "if you were to lie down in one and take a long snooze. "+
    "The window on the wall has the shutters drawn so you will "+
    "not be bothered by the sunshine while you are trying to rest. "+
    "There is a sign on the wall with further instructions.\n");


   add_item(({"wall","sign","window","shutters"}),
   "The well-worn walls are made of a fine wood, stained only "+
   "by age. There is a circular window complete with shutters "+
   "about three feet off the ground. A sign on the wall catches "+
   "your eye:\n"+
   "You may spend the night here by typing 'start here'.\n");

   add_item(({"floor","ground","lodgings","bed","beds"}),
   "This is the Prancing Pony's innroom. The beds are in good "+
   "order and everything seems reasonably clean, even the floor. Not that "+
   "you care- you are ready for sleep, most likely.\n");

  add_exit(BREE_DIR + "inn", "west", 0, 2,);

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

init()
{
  ::init();

    add_action("start","start");
    add_action("check_time","time");
    add_action("read_sign","read");
}
int start(string s)
{
  object ob;

  if(!(ob=present("inn_key",TP)))
     {
       write("You don't have the key you need!\n");
       return 1;
     }
  NF("Start where?\n");
  if(s!="here") return 0;

  ob->remove_object();

  TP->set_temp_start_location(BREE_DIR + "innroom");
     write_file("/d/Shire/log/hotel",TP->query_name()+" chose the "
     + "Prancing Pony as temporary starting location on "
     + ctime(time()) + ".\n");

     write(BS("You notice that the small wooden key fits well for the situation at "
     	+ "hand. You are confident that you will wake up here the next "
        + "time you enter the game.\n"));
  return 1;
   }

int
read_sign(string str)
{
   if(str != "sign")
     {
     write("You cannot make out the words to "+str+", it's too dark.\n");
      return 1;
      }
   write("In the dim light, you make out the words: \n"+
         "To stay the night, type 'start here'\n");
     return 1;

}
