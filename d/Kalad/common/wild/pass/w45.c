/* 
 * /d/Kalad/common/wild/pass/w45.c
 * Purpose    : Setting
 * Located    : South of Caravan Route
 * Created By : Antharanos Whenver
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

/* by Antharanos */

private object scout;

create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Niche");
   set_long("This appears to be a dead end valley, for lying to the north "+
      "is the sheer face of a mountain. Growing all about you are massive "+
      "redwood trees, rising so high that their green canopies block out "+
      "large sections of the sky. A large cleft lies in the south, apparently "+
      "leading to another valley.\n");
   add_item(({"valley"}),"Its what you are inside of, duh.\n");
   add_item(({"sheer face","face","mountain"}),"One of the mountains of "+
      "the great Hespyre range, it lies to the north, marking the end of "+
      "this small vale.\n");
   add_item(({"massive redwood trees","redwood trees","massive trees","trees","tree"}),
      "As large as twenty feet across at their base, these huge plants rise "+
      "hundreds of feet into the air, with their many leaves forming a green "+
      "canopy over the vale.\n");
   add_item(({"green canopies","green canopy","canopies","canopy"}),"Only "+
      "small sections of the azure blue sky are visible due to the many "+
      "trees blocking your vision. As a result, there is an abundance of "+
      "shady areas on the forest floor.\n");
   add_item(({"large cleft","cleft"}),"Past several twisting rock walls "+
      "you catch a glimpse of a narrow road, the Caravan Route.\n");
   add_exit("/d/Kalad/common/wild/pass/w13", "south",0,2);
   reset_room();
}

public void
reset_room()
{
   if(!scout)
   {
      scout = clone_object("/d/Kalad/common/wild/pass/raid_base/npc/fang_scout");
      scout->move(this_object(), 1);
      scout->arm_me();
   }
}
