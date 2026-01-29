/* Window on the backside of the city council building */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "filter_funs.h"
#include "language.h"
#define DOWN_ROOM "/d/Kalad/common/central/circle/s1"
#define WINDOW_ROOM "/d/Kalad/common/central/circle/wr"
int open_window;
int window_picked;
int window_broken;




create_room()
{
   ::create_room();
   hear_bell = 3;
   set_short("Window");
   set_long("You cling onto the wall, trying not to fall down. "+
      "Above you there is a window. @@open_locked_window@@ @@broken@@\n");
   set_time_desc("You have a splendid view from here. To the "+
      "northwest you see a huge bronze bell shine in the sun "+
      "inside the Citadel's tower, and far away to the south you "+
      "can see something huge sparkling with a blue colour in "+
      "the sun; It must be the sea.\n",
      "Since it's night time here in Kalad you cannot see much "+
      "of the town from here, except a few lights in some of the office "+
      "buildings across circle street.\n");
   add_item("window","@@check_awareness");
   add_exit(CENTRAL(circle/s14),"down",0,1);
   window_picked = 0;
   open_window = 0;
   window_broken = 0;
}

void
init()
{
   ::init();
   add_action("enter_window","enter");
   add_action("open_window","open");
   add_action("pick_window","pick");
   add_action("break_window","break");
}

check_awareness()
{
   object *inv;
   object *live;
   object room;
   int someone_inside;
   if (TP->query_skill(SS_AWARENESS)<=20)
      return("It is a large window with coloured glass, making it very "+
      "hard to see anything inside it.\n");
   
   room = find_object(WINDOW_ROOM);
   if(!objectp(room))
      {
      someone_inside = 0;
   }
   else
      {
      inv = all_inventory(room);
      live = FILTER_LIVE(inv);
      someone_inside = sizeof(live);
   }
   if (someone_inside)
      {
      return("It is a large window with coloured glass, making it very "+
         "hard to see anything inside it. You hear a faint breathing coming "+
         "from within, making it clear that the room is occupied right "+
         "now.\n");
   }
   else
      {
      return("It is a large window with coloured glass, making it very "+
         "hard to see anything inside it. You cannot hear or see moving "+
         "inside, so you guess it's empty.\n");
   }
}

string
open_locked_window()
{
   if (open_window) return "You notice that it is open.";
   return "You notice that it is closed.";
}

string
broken()
{
   if (window_broken) return "The glass of the window is shattered, "+
      "with sharp pieces of glass still hanging jaggedly"+
      "onto the windows frame.";
   return "";
}


int
break_window(string str)
{
   string text;
   notify_fail("Break what?\n");
   if (!str) return 0;
   if (str != "window") return 0;
   notify_fail("But the window is already broken!\n");
   if(window_broken) return 0;
   TP->catch_msg("You smash the window into pieces, making the glass "+
      "fly into the room with a thundering sound!\n");
   say(QCTNAME(TP)+" smashes the window, sending the glass "+
      "flying into the room with a thundering sound!\n");
   TP->catch_msg("Several guards comes running inside the room, "+
      "opens the window and drags you inside. You are firmly hold fast.\n");
   say("Several guards comes running inside the room, opens the "+
      "window and drags "+QTNAME(TP)+" away screaming.\n");
   TP->move_living("towards jail accompanied by several guardsmen","/d/Kalad/common/trade/jail");
   window_broken = 1;
/* removed bc. a wierd runtime error
   text = "and "+capitalize(TP->query_real_name())+" has been "+
      "put in jail for crimes unspeakable.";
   call_other(CENTRAL(high-circle-south),"patrol_text",text);
this ends the comment. Korat  */
   return 1;
}


int
open_window(string str)
{
   notify_fail("Open what?\n");
   if (!str) return 0;
   if (str != "window") return 0;
   notify_fail("The window is locked!\n");
   if (!window_picked) return 0;
   notify_fail("Its too heavy! You give up opening it.\n");
   if (TP->query_base_stat(SS_STR) < 60) return 0;
   TP->catch_msg("You open the window.\n");
   say(QCTNAME(TP)+" opens the window.\n");
   open_window=1;
   return 1;
}

int
pick_window(string str)
{
   notify_fail("Pick what?\n");
   if(!str) return 0;
   notify_fail("But the window is unlocked!\n");
   if (window_picked) return 0;
   TP->catch_msg("You try to pick the lock of the window...\n");
   say(QCTNAME(TP)+" tries to do something to the window.\n");
   notify_fail("And you fail!\n");
   if (TP->query_skill(SS_OPEN_LOCK) < 10)
   {
      write("But you fail in your attempt...\n");
      return 1;
   }
   TP->catch_msg("And you succeed!\n");
   say("You guess by the happy sounds "+QTNAME(TP)+" makes that "+
      TP->query_pronoun()+" succeeded doing whatever "+TP->query_pronoun()+
      " was trying to do.\n");
   window_picked=1;
   return 1;
}

int
enter_window(string str)
{
   
   notify_fail("Enter what?\n");
   
   if (!str)
      return 0;
   if (str != "window")
      return 0;
   
   notify_fail("You start to enter the broken window, but give up after "+
         "cutting yourself severely on the shattered pieces of glass.\n");
   if (window_broken && !open_window) return 0;
   notify_fail ("It's closed.\n");
   if (!open_window) return 0;
   TP->catch_msg("You slowly crawl inside the window.\n");
   say(QCTNAME(TP)+ " slowly crawls inside the window.\n");
   TP->move_living("enters the window.",WINDOW_ROOM,1);
   return 1;
}

