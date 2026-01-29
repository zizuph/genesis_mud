/* 
 * /d/Kalad/common/wild/pass/w42.c
 * Purpose    : Valley setting
 * Located    : South of Caravan Route
 * Created By : Antharanos *shrug*
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
void reset_room();
void do_search();
int recently_searched;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Valley");
   set_long("A beautiful vista spreads out before you. "+
      "Filling your entire view is the beautiful "+
      "spectacle of an entire valley filled with towering redwoods. The "+
      "slopes of the Hespyre mountains are less sharp here and are low "+
      "enough in angle that the tree line is significantly higher here than "+
      "on other parts of the mountain range. The vale continues to the "+
      "south.\n");
   add_item(({"towering redwoods","redwoods","towering redwood","redwood"}),
      "Massive trees that are as large as twenty feet across at the base "+
      "and rise dozens of feet into the sky. Their thick canopies of leaves "+
      "in conjunction with their proximity produce an abundance of shade "+
      "beneath them, on the forest floor.\n");
   add_item(({"canopies","canopy","leaves"}),"They nearly block out the "+
      "sky.\n");
   add_item(({"forest floor","floor"}),"The ground is littered with "+
      "newly fallen leave, still green. Some bushes lie about the area.\n");
   add_item(({"bushes"}),"Thick green bushes that are scattered about the "+
      "forest floor.\n");
   add_item(({"slopes","hespyre mountains","mountains","mountain","mountain range","range"}),
      "They are perhaps only a third the height of the main mountain range "+
      "of the Hespyre mountains. However, this doesn't make them any less "+
      "impressive, as they are still dozens of times higher than the tallest "+
      "structure made by man.\n");
   add_exit("/d/Kalad/common/wild/pass/w41", "northwest",0,2);
   add_exit("/d/Kalad/common/wild/pass/w43", "south",0,2);
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
   add_action("search_bushes", "search");
}
int
search_bushes(string str)
{
   if(!str || str!= "bushes")
      return 0;
   if(recently_searched)
      {
      write("You find nothing within the bushes, and get a few scratches "+
         "for your effort.\n");
      return 1;
   }
   write("You start to search the bushes.\n");
   say(QCTNAME(TP) + " searches through the bushes.\n");
   set_alarm(4.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   recently_searched = 1;
   write("You find an interesting looking berry within the bushes.\n");
   say(QCTNAME(TP) + " takes something from the bushes.\n");
   clone_object("/d/Kalad/common/wild/pass/herbs/huckleberry")->move(TP);
   return;
}
