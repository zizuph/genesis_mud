/* 
 * /d/Kalad/common/wild/pass/w28.c
 * Purpose    : Valley setting
 * Located    : Hespyre Mountains
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
int pres,i;
object *ob;
#define GIANT "/d/Kalad/common/wild/pass/npc/hgiant"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Valley");
   set_long("You are within a widening valley.\n"+
      "The valley walls are much wider here than farther to the southeast. "+
      "Spreading out before you is the vista of a forest of redwood trees, boxed "+
      "in on the sides by the sheer cliff walls of the Hespyre mountains. Through "+
      "wide passages in the north and southeast the rest of the valley "+
      "lies.\n");
   add_item(({"forest","redwood trees","redwood tree","trees","tree"}),
      "Towering far above you are many huge trees, as large as twenty feet "+
      "in diameter at the base and rising hundreds of feet into the air. "+
      "Their expansive canopies create an abundance of shadows on the "+
      "forest floor.\n");
   add_item(({"expansive canopies","expansive canopy","canopies","canopy"}),
      "A ceiling of green is all you can see, with occasional bits of the "+
      "sky also visible.\n");
   add_item(({"sheer cliff walls","sheer walls","cliff walls","walls"}),
      "The sides of this valley are set at a steep angle, almost perpindicular "+
      "to the ground.\n");
   add_item(({"hespyre mountains","mountains"}),"They tower above the "+
      "forest just as the forest towers above you. They seem to cast a dark "+
      "shadow across the land.\n");
   add_exit("/d/Kalad/common/wild/pass/w29", "north","@@query_move",2);
   add_exit("/d/Kalad/common/wild/pass/w27", "southeast",0,2);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!ob1)
      {
      ob1 = clone_object(GIANT);
      ob1 -> move_living("xxx", TO);
   }
   if (!ob2)
      {
      ob2 = clone_object(GIANT);
      ob2 -> move_living("xxx", TO);
      ob1 -> team_join(ob2);
   }
}
query_move()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for (i = 0; i < sizeof(ob); i++){
      if (ob[i]->query_name() == "Giant"){
         pres = 1;
        }
   }
   if (pres == 1){
      write("The hill giant blocks your way with his foot!\n");
      say("The hill giant blocks the way north.\n");
   }
   return pres;
}
