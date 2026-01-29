inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Bend in the Caravan Route");
   set_long("The flat landscape here is only occasionally broken by the "+
      "slight rise of a hill, which are themselves relatively flat, being "+
      "covered only by hardy grasses. Like a black wall in the horizon are the "+
      "distant Hespyre mountains. The Caravan Route travels west towards the towering range while "+
      "to the southeast, where the land grows drier and more inhospitable, it "+
      "leads to the great Kalad waste.\n");
   add_item(({"flat landscape","landscape"}),"A great feeling of vast openness "+
      "fills your being as you gaze out at the area surrounding you. The effect, "+
      "however, is ruined by the few hills surrounding you.\n");
   add_item(({"hills","hill"}),"Small foothills that are blanketed by a layer "+
      "of hardy grasses, which seem to thrive in this somewhat dry environment.\n");
   add_item(({"hardy grasses","grasses","grass"}),"Tall, tough plants "+
      "that are perfectly suited to this land.\n");
   add_item(({"black wall","wall","hespyre mountains","mountains","mountain","towering range","range"}),
      "Even from this great distance, the massive range of mountains rises "+
      "above all other land forms, marking its preeminence in the geography "+
      "of this region.\n");
   add_item(({"caravan route","route"}),"A cobblestoned roadway that bears the "+
      "mark of long, heavy usage and harsh weather in its cracked and faded "+
      "facade.\n");
   add_exit(CPASS(goblin/g3),"west",0,2,1);
   add_exit(CPASS(desert/d1),"southeast","@@msg",3,1);
}
msg()
{
   write("A harsh, dry wind welcomes you to the Great Kalad Waste.\n");
   return 0;
}
