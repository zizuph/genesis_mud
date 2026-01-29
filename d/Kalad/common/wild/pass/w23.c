/* 
 * /d/Kalad/common/wild/pass/w23.c
 * Purpose    : Valley setting
 * Located    : Hespyre Mountains
 * Created By : Antharanos  
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
   set_long("You are within the confines of a narrow valley.\n"+
      "Spreading out before you is the vista of a forest of redwood trees, boxed "+
      "in on the sides by the sheer cliff walls of the Hespyre mountains. Through "+
      "narrow passages in the north and southeast the rest of the valley "+
      "lies.\n");
   add_item(({"forest","redwood trees","redwood tree","trees","tree"}),
      "Towering far above you are many huge trees, as large as twenty feet "+
      "in diameter at the base and rising hundreds of feet into the air. "+
      "Their expansive canopies create an abundance of shadows on the "+
      "forest floor.\n");
   add_item(({"forest floor","floor"}),"Vibrant grass blankets the "+
      "ground.\n");
   add_item(({"expansive canopies","expansive canopy","canopies","canopy"}),
      "A ceiling of green is all you can see, with occasional bits of the "+
      "sky also visible.\n");
   add_item(({"sheer cliff walls","sheer walls","cliff walls","walls"}),
      "The sides of this valley are set at a steep angle, almost perpindicular "+
      "to the ground.\n");
   add_item(({"hespyre mountains","mountains"}),"They tower above the "+
      "forest just as the forest towers above you. They seem to cast a dark "+
      "shadow across the land.\n");
   add_exit("/d/Kalad/common/wild/pass/w24", "north",0,2);
   add_exit("/d/Kalad/common/wild/pass/w22", "southeast",0,2);
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
   add_action("search_grass", "search");
}
int
search_grass(string str)
{
   if(!str || str != "grass")
      return 0;
   if(recently_searched)
      {
      write("You find a few holes in the moist earth, as if someone uprooted "+
         "some plants here.\n");
      return 1;
   }
   write("You start to search through the grass.\n");
   say(QCTNAME(TP) + " searches through the grass.\n");
   set_alarm(4.0,0.0,"do_search");
   return 1;
}
void
do_search()
{
   recently_searched = 1;
   write("You find an interesting piece of grass and dig it out of the "+
      "moist ground.\n");
   say(QCTNAME(TP) + " takes something from the grass.\n");
   clone_object("/d/Kalad/common/wild/pass/herbs/grass")->move(TP);
   return;
}
