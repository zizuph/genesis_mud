inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
/*
* This room includes two extra commands:
* 'spy through holes' and 'listen through holes'
* Both are part of a small quest.
*/


int listening;

create_room()
{
   ::create_room();
   hear_bell = 0;
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);
   set_short("hidden passage");
   set_long("You travel down the dark passage.\n"+
      "You can barely see this passageway, but it does lead "+
      "southwards through a lot of cobwebs.\n");
   add_item("cobweb","They hang from the walls, the ceiling, everywhere.\n");
   add_item(({"wall","walls"}),"The walls are made of stone that "+
      "are cold to the touch. On the western wall you notice two "+
      "small holes...\n");
   add_item("holes","They are at eye-level, and looks like..."+
      "two eyes?! Must be some spying-holes.\n");
   set_noshow_obvious(1);
   add_exit(CENTRAL(plaza/cl_hidden1),"south",0,-1,2);
   listening = 0;
}

init()
{
   ::init();
   add_action("spy","spy");
   add_action("listen","listen");
}

spy(string str)
{
   notify_fail("Spy through what?\n");
   if (!str || str!="through holes")
      return 0;
   write("You look through the holes, and you suddenly "+
      "see some of the lords talking to each other!\n");
   return 1;
}

listen(string str)
{
   notify_fail("Listen through what?\n");
   if (!str || str!="through holes") return 0;
   notify_fail("Someone else is already listening through the holes!\n");
   if (listening) return 0;
   write("You put your ear to one of the holes.\n");
   listening = 1;
   set_alarm(3.0,0.0,"talk0");
   return 1;
}

talk0()
{
   if (!player_here())
      {
      listening = 0;
      return;
   }
   write("You hear a voice say: ...omething about that man.\n");
   set_alarm(1.0,0.0,"talk1");
}
talk1()
{
   if(!player_here())
      {
      listening = 0;
      return;
   }
   write("A deep voice says: Yes!\n");
   set_alarm(3.0,0.0,"talk2");
}
talk2()
{
   if(!player_here())
      {
      listening = 0;
      return;
   }
   write("A voice wonders: But what? Kill him?? Too drastic!\n");
   set_alarm(2.0,0.0,"talk3");
}
talk3()
{
   if (!player_here())
      {
      listening = 0;
      return;
   }
   write("A deep voice chuckles.\n");
   set_alarm(2.0,0.0,"talk4");
}
talk4()
{
   if(!player_here())
      {
      listening = 0;
      return;
   }
   write("A deep voice agrees: Yeahh...but we can bankrupt him.\n");
   set_alarm(4.0,0.0,"talk5");
}
talk5()
{
   if(!player_here())
      {
      listening = 0;
      return;
   }
   write("A voice says: Hmm, lets contact the trading company's Lord.\n");
   set_alarm(3.0,0.0,"talk6");
}
talk6()
{
   if(!player_here())
      {
      listening = 0;
      return;
   }
   write("A deep voice says: Lets do that.\n");
   set_alarm(3.0,0.0,"talk7");
}
talk7()
{
   if(!player_here())
      {
      listening = 0;
      return;
   }
   write("A deep voice chuckles.\n");
   set_alarm(8.0,0.0,"talk8");
}
talk8()
{
   if(!player_here())
      {
      listening = 0;
      return;
   }
   write("A deep voice says: He will know how to destroy Bocca...\n");
   set_alarm(4.0,0.0,"talk9");
}
talk9()
{
   if (!player_here())
      {
      listening = 0;
      return;
   }
   write("You decide to have a look and put your eye to the hole.\n");
   write("You can see a grumpy old man put fire to a note. Its burning..."+
      "That must be the proof you need! Better hurry...\n");
   call_other(CENTRAL(plaza/cl_deb),"make_note");
   listening = 0;
}

int
player_here()
{
  int i;
   object *ob;
   ob = FILTER_LIVE(all_inventory(TO));
   for (i=0;i<sizeof(ob);i++) if (ob[i]->query_real_name()==TP->query_real_name()) return 1;
   return 0;
}
