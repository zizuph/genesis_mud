/* 
 * /d/Kalad/common/wild/pass/giantpass/rooms/w31.c
 * Purpose    : Setting with npcs
 * Located    : North west in Hespyre Mountains
 * Created By : Antharanos  
 * Modified By: Meton 2020
 */ 

#include "../local.h"
inherit STDIR + "giantroom_std.c";

void reset_room();
void do_search();
int recently_searched;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("Hill Giant Village");
   set_long("You've entered a large clearing surrounded by several giant "
      + "huts. In the center of the clearing is a huge stone monument. "
      + "Looking around at your surroundings you note several piles of "
      + "refuse scattered about the clearing. One large hut, of even "
      + "greater size than the  rest lies just to the north.\n");
   add_item(({"large clearing","clearing"}),"A large area around sixty "
      + "feet in diameter that is devoid of plant life, but is filled "
      + "with several piles of refuse.\n");
   add_item(({"refuse"}),"It is heaped in piles all about the "
      + "clearing.\n");
   add_item(({"piles"}),"Different odds and ends can be seen, with "
      + "discarded bits of metal and wood being most prominent.\n");
   add_item(({"huge stone monument","huge monument","stone monument",
      "monument"}),
      "Unfortunately for you, an all too realistic portrayal of a large, "
      + "and grotesque looking humanoid, probably a hill giant by the "
      + "stooping ape-like posture. Plastered on the giant's face is an "
      + "utterly repulsive grin.\n");
   add_item(({"giant huts"}),"Four huts can be seen, to the southwest, "
      + "northwest, northeast and southeast.\n");
   add_item(({"large hut"}),"A huge hut, It looks like the home of the "
      + "leader of this village.\n");
   add_exit(RDIR + "swhut", "southwest");
   add_exit(RDIR + "nwhut", "northwest");
   add_exit(RDIR + "nhut", "north");
   add_exit(RDIR + "nehut", "northeast");
   add_exit(RDIR + "sehut", "southeast");
   add_exit(RDIR + "w30", "south");
   reset_room();
}

void
reset_room()
{
   recently_searched = 0;
}

void
init()
{
   ::init();
   add_action("search_piles", "search");
}

int
search_piles(string str)
{
   if(!str || str!= "piles")
      return 0;
   if (recently_searched)
   {
      write("You find nothing but a few dung beetles that you quickly brush "+
         "off yourself.\n");
      return 1;
   }
   write("You start to search the piles.\n");
   say(QCTNAME(TP) + " starts to search the piles.\n");
   set_alarm(4.0,0.0,"do_search");
   return 1;
}

void
do_search()
{
   recently_searched = 1;
   write("You find an interesting piece of scrap metal.\n");
   say(QCTNAME(TP) + " takes something from the piles.\n");
   clone_object("/d/Kalad/common/wild/pass/obj/iron")->move(TP);
   return;
}
