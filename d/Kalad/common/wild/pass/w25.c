/* 
 * /d/Kalad/common/wild/pass/w25.c
 * Purpose    : Valley setting
 * Located    : Hespyre Mountains
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Valley");
   set_long("You are within the confines of a narrow valley.\n"+
      "Spreading out before you is the vista of a forest of redwood trees, boxed "+
      "in on the sides by the sheer cliff walls of the Hespyre mountains. Through "+
      "narrow passages in the northeast and southwest the rest of the valley "+
      "lies. A huge gash in the side of the mountains is to the southeast.\n");
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
      "to the ground. There is gash in the mountainside to the southeast.\n");
   add_item(({"huge gash","gash"}),"It as if a great axe cleaved a chunk "+
      "of the mountainside away, revealing a pass through the mountains.\n");
   add_item(({"hespyre mountains","mountains"}),"They tower above the "+
      "forest just as the forest towers above you. They seem to cast a dark "+
      "shadow across the land.\n");
   add_exit("/d/Kalad/common/wild/pass/giants/rooms/w26", "northeast",0,2);
   add_exit("/d/Kalad/common/wild/pass/w35", "southeast",0,2);
   add_exit("/d/Kalad/common/wild/pass/w24", "southwest",0,2);
}
