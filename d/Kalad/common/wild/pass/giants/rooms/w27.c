/* 
 * /d/Kalad/common/wild/pass/w27.c
 * Purpose    : Valley setting
 * Located    : Hespyre Mountains
 * Created By : Antharanos  
 * Modified By: Meton 2020
 */ 

#include "../local.h"
inherit STDIR + "giantroom_std.c";

/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("Valley");
   set_long("You are within a widening valley.\n"
      + "The valley walls are wider here than further to the south. "
      + "Spreading out before you is the vista of a forest of redwood "
      + "trees, boxed in on the sides by the sheer cliff walls of the "
      + "Hespyre mountains. Through narrow passages in the northwest and "
      + "south the rest of the valley lies.\n");
   add_item(({"forest","redwood trees","redwood tree","trees","tree"}),
      "Towering far above you are many huge trees, as large as twenty "
      + "feet in diameter at the base and rising hundreds of feet into "
      + "the air. Their expansive canopies create an abundance of shadows "
      + "on the forest floor.\n");
   add_item(({"expansive canopies","expansive canopy","canopies",
      "canopy"}),
      "A ceiling of green is all you can see, with occasional bits of "
      + "the sky also visible.\n");
   add_item(({"sheer cliff walls","sheer walls","cliff walls","walls"}),
      "The sides of this valley are set at a steep angle, almost "
      + "perpindicular to the ground.\n");
   add_item(({"hespyre mountains","mountains"}),"They tower above the "
      + "forest just as the forest towers above you. They seem to cast a "
      + "dark shadow across the land.\n");
   add_exit(RDIR + "w28", "northwest",0,2);
   add_exit(RDIR + "w26", "south",0,2);
   add_npc(LIV + "hgiant.c", 1);
}