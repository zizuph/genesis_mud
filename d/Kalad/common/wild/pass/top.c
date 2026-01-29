/* 
 * /d/Kalad/common/wild/pass/top.c
 * Purpose    : Location for important quest NPC
 * Located    : Just north of Kabal gates
 * Created By : Antharanos  
 * Modified By: 
 */ 

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/composite.h"
/* by Antharanos */
object ob1;
void
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Mountaintop");
   set_long("The vista up here is truly amazing!\n"+
      "You are now at the very summit of this mountaintop, gazing all around "+
      "you, you can see countless mountains. Looking far to the west a "+
      "huge chasm can be seen. Southwest, far off in the distance is a "+
      "large city. Finally, turning to the east, your eyes pick out the "+
      "thin line that is the Caravan Route as it heads eastwards out of the "+
      "mountains into a large flat expanse, the Kalad waste.\n");
   add_item(({"mountains"}),"The great peaks of the mountains can be "+
      "seen all around you. Some of the higher peaks are enshrouded in "+
      "thick white clouds, so great is their height.\n");
   add_item(({"huge chasm","chasm"}),"A huge rent in the surface of the "+
      "earth, you wonder what could have caused such a massive hole in "+
      "the ground.\n");
   add_item(({"large city","city"}),"A walled city, even from this great "+
      "distance, individual buildings can be seen, though no clear details "+
      "are visible.\n");
   add_item(({"caravan route","route"}),"From your vantage point, it "+
      "appears as nothing more than a line drawn upon the ground.\n");
   add_item(({"kalad waste","waste"}),"A desert lying far to the east, "+
      "and seemingly going on forever.\n");
   
   set_alarm(1.0,0.0,"reset_room");
}

void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/climber");
      ob1 -> move_living("M",TO);
      tell_room(TO,"A lonely dwarf at the far end of the mountain suddenly "+
         "catches your attention.\n");
   }
}
void
init()
{
   ::init();
   
   add_action("try_climb", "climb");
   add_action("jump", "jump");
   add_action("xthrow", "throw");
}

int
try_climb(string str)
{
   notify_fail("Climb what, down?\n");
   
   if (!str || str != "down")
      return 0;
   
   this_player()->move_living("climbing down", "/d/Kalad/common/wild/pass/shaft",1);
   this_player()->add_fatigue(-5);
   return 1;
}

int
jump(string str)
{
   write("You try to jump as high as possible and you slip. It's seems to " +
      "be a long\nway down....\n");
   say(QCTNAME(this_player()) + " foolishly jumps and falls from the mountaintop.\n");
   
   this_player()->move_living("M", "/d/Kalad/common/wild/pass/falling",1);
   return 1;
}

int
xthrow(string str)
{
   object *arr;/* Local variables, array of objects */
   int i;/* Local variable, integer, used in the for-loop */
   
   if (!str)
      {
      notify_fail("Throw what?\n");
      return 0;
   }
   
   arr = FIND_STR_IN_OBJECT(str, this_player());
   
   if (!sizeof(arr))
      {
      notify_fail("You don't have any '" + str + "'.\n");
      return 0;
   }
   
   for (i = 0; i < sizeof(arr); i++)
   arr[i]->move("/d/Kalad/common/wild/pass/falling");
   
   write("You throw " + COMPOSITE_DEAD(arr) + " off the mountaintop.\n");
   say(QCTNAME(this_player()) + " throws " + QCOMPDEAD + " off the mountaintop.\n");
   return 1;
}
