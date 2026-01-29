/*
ROOM: Hallway upstairs
BY: Korat
Date: Feb 14, 1995
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;

void
create_room()
{
   ::create_room();                         
   hear_bell = 2;                           
   
   set_short("The City Council; The Lords office");
   set_long(
      "This large and decorated room belongs to "+
      "a important person; here the City Council's Lord performs his "+
      "duties. There are some windows, a "+
      "large bookshelf on the southern wall, and an impressive desk "+
      "in the middle of the room, but not much else to rest your "+
      "eyes on.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_item(({"window","windows"}),"Some plain windows, inserted into "+
      "the northern and western wall.\n");
   add_item("desk","Its a large wooden desk, littered with typical "+
      "things a desk contains.\n");
   add_item("bookshelf","Its a huge bookshelf, almost covering all the "+
      "southern wall.\n");
   add_item(({"book","books"}),"Ohh, you see...a lot of books. All pretty boring.\n");
   add_exit(CENTRAL(plaza/cc_up),"east",0,-1,-1);
   set_alarm(0.0,0.0,"reset_room");
}

init()
{
   ::init();
   add_action("search","search");
}

search(string str)
{
   notify_fail("Search what?\n");
   if (!str) return 0;
   if (str == "bookshelf")
      {
      write("You start to search the bookshelf.\n");
      set_alarm(5.0,0.0,"s_bookshelf");
      return 1;
   }
   if (str=="books")
      {
      write("You start to search the books.\n");
      set_alarm(5.0,0.0,"s_books");
      return 1;
   }
   return 0;
}

s_bookshelf()
{
   switch (TP->query_skill(SS_AWARENESS))
   {
      case 0..10: write("Your search reveals nothing special.\n"); break;
      case 11..20: write("You find nothing special, but you "+
         "you still have a feeling of something about that bookshelf.\n"); break;
      case 21..40: write("You realise that there is something wrong with this "+
         "bookshelf, but what?\n"); break;
      default: write("You realize that the bookshelf contains a hidden door! But "+
         "after a while, you also realize that you can't open it.\n"); break;
   }
}

s_books()
{
   write("Your search reveals nothing special.\n");
}

reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/militia_plaza");
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      ob1 -> command("peer all");
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/militia_plaza");
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      ob2 -> command("emote comes in sighing to stand guard.");
      ob1 -> team_join(ob2);
   }
   if(!objectp(ob3))
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/bocca");
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
      ob1 -> team_join(ob3);
      ob3 -> command("emote yawns loudly as he arrives to "+
         "start his work for the day.");
   }
}
