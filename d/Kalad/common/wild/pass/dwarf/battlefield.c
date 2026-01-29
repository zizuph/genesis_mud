inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object axe;
int axe_here;
/* by korat */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("A part of the plains outside Kabal");
   set_long("You have arrived at the plains outside the "+
      "large city of Kabal. All around you there are tall "+
      "grass growing in the hot sun, When you walk up on a mound "+
      "close by you can see the tall citywalls to the south and "+
      "the large plain stretching out, only scarred by the road "+
      "west of you. Some farms are visible, surrounded by "+
      "large fields.\n");
   add_item("mound","The mound is one of many around here. One this one you "+
      "see a halfway burried rock.\n");
   add_item("rock","You bend down and brush the earch and grass away "+
      "from it. There is some kind of writing onit: 'here lies "+
      "Oxarnt, hero of the wars of races.'.\n");
   add_item(({"walls","city walls","kabal","Kabal","city"}),
      "The city with its large walls lies to the south. An impressive sight.\n");
   add_item(({"plain","plains"}),
      "The plains stretch faar out towards most directions.\n");
   add_item("road","It is west of you. The famous caravan road.\n");
   add_item("grass","The brown grass bends slightly in the northern wind.\n");
   add_item(({"field","fields"}),"The fields seems to be of a golden "+
      "colour. Probably axes of wheat being grown there.\n");
   add_item(({"farm","farms"}),"The farms are far away from you, "+
      "but you notice some creatures around it. Probably only the "+
      "farmers.\n");
   add_exit(CPASS(w2),"west");
   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}

reset_room()
{
   axe_here = 1;
}

init()
{
   ::init();
   add_action("digging","dig");
}

digging(string str)
{
   notify_fail("Dig what?\n");
   if (!str) return 0;
   notify_fail("You can't dig in that.\n");
   if (str!="mound") return 0;
   TP->catch_msg("You start to dig in the mound.\n");
   tell_room(TO,QCTNAME(TP)+" starts to dig in the mound.\n",TP);
   set_alarm(5.0,0.0,"dig_result",TP);
   return 1;
}

dig_result(object who)
{
   if(present(who))
      {
      if(axe_here)
         {
         who->catch_msg("After digging for a while you find "+
            "an old axe.\n");
         tell_room(TO,QCTNAME(who)+" finds something.\n",who);
         axe = clone_object(CPASS(dwarf/wep/mag_axe));
         axe -> move(who);
         axe_here = 0;
      }
      else
         {
         who->catch_msg("You don't find much here.\n");
      }
      return;
   }
}
