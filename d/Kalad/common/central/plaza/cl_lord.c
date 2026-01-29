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
int note_found;

void
create_room()
{
   ::create_room();                         
   hear_bell = 2;                           
   
   set_short("The Lord Council; The chairmans office");
   set_long(
      "As a pretty large, and decorated room, it must belong to "+
      "some important person; here the chairman of the Lord's council does his "+
      "duties belonging to his position. Except for some windows, a "+
      "large bookshelf on the southern wall and an impressive desk "+
      "in the middle of the room, there is not much else to rest your "+
      "eyes on. Especially so, since the chairman is not here.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   
   add_item(({"window","windows"}),"Some plain windows, inserted into "+
      "the northern and eastern wall.\n");
   add_item("desk","Its a large wooden desk, littered with typical "+
      "things a desk contains. There is a paper basket below it.\n");
   add_item("bookshelf","Its a huge bookshelf, almost covering all the "+
      "southern wall.\n");
   add_item(({"book","books"}),"Ohh, you see...a lot of books. All pretty boring.\n");
   add_item(({"basket","paper basket"}),"It's a plain paper "+
      "basket with some crumpled sheets in it.\n");
   add_exit(CENTRAL(plaza/cl_up),"west",0,-1,-1);
   set_alarm(0.0,0.0,"reset_room");
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
      ob2 -> team_join(ob1);
   }
   note_found = 0;
}



init()
{
   ::init();
   add_action("search","search");
}

search(string what)
{
   if (!what || what != "basket") return 0;
   if (note_found)
      {
      write("You search through the basket, but find nothing interesting.\n");
      return 1;
   }
   write("You start to search the paper basket.\n");
   set_alarm(5.0,0.0,"do_search");
   return 1;
}

do_search()
{
   note_found = 1;
   write("After thorougly searching the basket, you decide its "+
      "really nothing interesting with it. You did find a piece of paper "+
      "though that you picked up.\n");
   say(QCTNAME(TP)+" picked something up from the paper basket.\n");
   clone_object("/d/Kalad/common/central/obj/lord_grant")->move(TP);
   return;
}
