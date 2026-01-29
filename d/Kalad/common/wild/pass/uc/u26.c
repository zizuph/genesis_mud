inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define KNIGHT "/d/Kalad/common/wild/pass/uc/npc/thanar_knight"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A sewer passage");
   set_long("A sewer passage.\n"+
      "Stone as obsidian as the desires of fell and evil beings surrounds "+
      "you from all directions, holding you in its cold, unyielding "+
      "embrace. An odor, reminiscent of filth and decay pervades the area, "+
      "causing you to avert your nose in disgust. Above lies only the "+
      "impenetrable barrier of rock that lies between this realm of stone "+
      "and darkness and the realm of life and the sun. The passage you are "+
      "within runs to the west and east. A small stream of filthy water "+
      "lies at the center of this sewer passage, forming into a small "+
      "pool to the east, where the ground is lower.\n"+
      "Almost unnoticed is a small passage that leads directly north.\n");
   add_item(({"sewer passage"}),
      "A sewer tunnel located beneath the streets of the city-state of Kabal.\n");
   add_item(({"small passage"}),
      "All that is visible is darkness...\n");
   add_item(({"passages"}),
      "You can't examine them both at once.\n");
   add_item(({"passage"}),
      "Which passage?\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_item(({"small stream","stream","filthy water","water"}),
      "Disgusting, brackish water, filled with unidentified bits of matter.\n");
   add_item(({"matter","unidentified bits","bits","bit"}),
      "It is best not to look at such filthy things.\n");
   add_item(({"small pool","pool"}),
      "A gathering of the filthy water, where there is a slight depression in "+
      "the floor of the passage. A depression that increases the further "+
      "east one travels.\n");
   add_exit(CPASS(uc/u25),"west","@@check",2,1);
   add_exit(CPASS(uc/t1),"north",0,2,1);
   add_exit(CPASS(uc/u27),"east",0,2,1);
   set_alarm(1.0,0.0,"reset_room");
   clone_object(CPASS(uc/obj/torch_stand))->move(TO);
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(KNIGHT);
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(KNIGHT);
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      tell_room(TO,"A pair of guardian knights of Thanar arrive to take their post.\n");
   }
}
check()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Knight")
         {
         pres = 1;
       }
   }
   if(pres == 1)
      {
      write("The guardian knight of Thanar stops you from going west.\n");
      say("The guardian knight of Thanar stops " + QTNAME(TP) + " from going west.\n");
   }
   return pres;
}
