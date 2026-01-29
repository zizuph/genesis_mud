/* Archive room in City council */
/* made by Korat */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
int found;

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   set_short ("The archive room");
   set_long (
      "All the walls in this room is covered by bookshelves. The air "+
      "tastes as dry as only old books and parchments can make it, "+
      "marking this room as a place for studious and hard-working "+
      "officials. Feather pens, some books and piles of sheets cover "+
      "a long, wooden table in the centre of the room. On the western "+
      "wall you see the window you came through.\n");
 
   add_item("window","Its made of coloured glass, making it hard to see "+
      "through it. It is open.\n");

   add_item (({"shelf","shelves"}),"They cover the walls all "+
      "around you, stuffed to the rim with large dustcovered books.\n");

   add_item ("table","The large wooden table is littered with "+
      "sheets of paper, feather pens and huge books.\n");

   add_item (({"sheet","sheets","paper","papers"}),
      "You study the papers carefully. Ack! Numbers, numbers and "+
      "numbers...what a boring life the officials must have. "+
      "Most of the papers seems "+
      "to be accounts of salaries, food, tools and other things. "+
      "Boring stuff really.\n");

   add_item (({"wall","walls"}),"The walls are too covered in "+
      "shelves for you to study them closer. You think they are "+
      "made of some kind of stone though since the outer wall was "+
      "made of that.\n");
   set_alarm(0.0,0.0,"reset_room");
   set_alarm(0.0,120.0,"check_room");
}
void
init()
{
   ::init();
   add_action("enter_window","enter");
   add_action("search_books","search");
}

int
search_books(string str)
{
   notify_fail("Search what?\n");
   if (!str) return 0;
   if (str = "books")
   {
      write("You start to search the books.\n");
      if (TP->query_skill(SS_LANGUAGE) < 30)
      {
         write("After a while you stop searching the books. You "+
            "don't understand anything of them anyway, so why "+
            "waste the time.\n");
         return 1;
      }
      set_alarm(5.0,0.0,"found_books");
      return 1;
   }
   set_alarm(5.0,0.0,"found_nothing");
   return 1;
}

found_nothing()
{
   write("You find nothing interesting.\n");
}

found_books()
{
   if (!found)
   {
      write("After a while you decide that most of the books "+
         "are pretty uninteresting. All you see is a lot of "+
         "accounting books with piles of numbers in them, all "+
         "dusted down after years of storage. Except three..."+
         "You pick them down.\n");
   /* clone books... */
      found = 1;
   }
   else
   {
      write("You search and search, but find nothing interesting.\n");
   }
}

int
enter_window(string str)
{
   notify_fail("Enter what?\n");

   if (!str)
      return 0;
   if (str != "window")
      return 0;

   write("You open the window slowly, and crawl through it.\n");
   say(QCTNAME(TP) + " starts to open the window, and crawls "+
   "through it.\n");
   TP->move_living("enters the window.","/d/Kalad/common/central/circle/window",1);
   return 1;
}

void
reset_room()
{
   found = 0;
}

check_room()
{
   if (TIME > 9 && TIME < 22) 
   {
      tell_room(TO, "A cleaning lady enters the room.\n");
      tell_room(TO, "She sees you and screams up!\n"+
         "A servant shouts: A BURGLAR IS IN HERE!!! GUUAARRRDDDDSSSS!!!! "+
         "HEEEEELLLPP!\n Then she runs out with a yell.\n");
      set_alarm(3.0,0.0,"arrest_player");
   }
   else
   {
      if (objectp(ob1)) destruct ob1;
      if (objectp(ob2)) destruct ob2;
      if (objectp(ob3)) destruct ob3;
      if (objectp(ob4)) destruct ob4;
      if (objectp(ob5)) destruct ob5;
   }
}

arrest_player()
{
   if (!objectp(ob1))
   {
      ob1 = clone_object("/d/Kalad/common/central/npc/officer1");  
      ob1 -> arm_me();
      ob1 -> move_living("An officer comes running into the room with weapons drawn.",TO);
      ob1 -> command("shout DIE, You wretch of a THIEF!!");
   }
   if (!objectp(ob2))
   {
      ob2 = clone_object("/d/Kalad/common/central/npc/guard1");
      ob2 -> arm_me();
      ob2 -> move_living("Several guards comes storming in, following their officer.", TO);
      ob2 -> team_join(ob1);
   }
   if (!objectp(ob3))
   {
      ob3 = clone_object("/d/Kalad/common/central/npc/guard1");
      ob3 -> arm_me();
      ob3 -> move_living("M", TO);
      ob3 -> team_join(ob1);
   }
   if (!objectp(ob4))
   {
      ob4 = clone_object("/d/Kalad/common/central/npc/guard1");
      ob4 -> arm_me();
      ob4 -> move_living("M", TO);
      ob4 -> team_join(ob1);
   }
   if (!objectp(ob5))
   {
      ob5 = clone_object("/d/Kalad/common/central/npc/guard1");
      ob5 -> arm_me();
      ob5 -> move_living("M", TO);
      ob5 -> team_join(ob1);
   }
}

