#include <ss_types.h>

#include "defs.h"

inherit TRICKSTER_STD_ROOM;
inherit "/lib/skill_raise";

void set_up_skills() 
{
 sk_add_train(SS_STRANGLE,"strangle using rumel","strangle",50,100);
 sk_add_train(SS_LOC_SENSE,"sense location",0,0,50);
 sk_add_train(SS_WEP_CLUB,"fight with clubs",0,0,50);
 sk_add_train(SS_FR_TRAP,"find and remove traps",0,0,30);
 sk_add_train(SS_LANGUAGE,"understand different languages",0,0,50);
 sk_add_train(SS_ALCHEMY,"mix potions",0,0,20);
 sk_add_train(SS_AWARENESS,"be aware of surroundings",0,0,60);
 sk_add_train(SS_SNEAK,"sneak",0,0,60);
 sk_add_train(SS_HIDE,"hide",0,0,60);
 sk_add_train(SS_TRADING,"trade",0,0,60);
 sk_add_train(SS_PARRY,"parry attacks",0,0,50);
}

public varargs int sk_query_max(int snum, int silent)
{
 int mx;

 mx=TP->query_trickster_level()*7;
 if(mx>100) mx=100;
 if(snum==SS_STRANGLE) return mx;
 return ::sk_query_max(snum, silent);
}

void create_room()
{
 set_short("Tricksters' Training Room");
 set_long(BS(
   "This room has a layer of water coating the floor, nearly ankle-deep."+
   "  Here Tricksters may train existing skills and learn new skills."+
   "  The walls are of scorched earth, and a medium-sized hole in the "+
   "southwest wall leads to a moist, poorly lit room.  As well there "+
   "is another brightly lit exit towards the southeast, from which loud "+
   "noises can be heard coming from. There is a sign on the floor "+
   "here.\n"));

 add_item(({"water","floor"}),"The thin layer of water that coats the "+
   "floor is thankfully clear, though walking around causes a bit of "+
   "squishing.\n");
 add_item(({"wall","walls"}),"The blackened earthen walls have been "+
   "scorched by intense heat, which obviously has escaped the water "+
   "on the floor.\n");
 add_item("hole","The hole leading to the poorly lid room is big enough "+
   "to accomodate all but the tallest people.\n");
 add_item("sign","While muddled with the mud and water on the floor, it "+
   "is still readable.\n");
 add_cmd_item("sign","read","This is the training room for the "+
   "Tricksters.\n");

 add_exit(TRICKSTERS+"discuss","southwest");
 add_exit(TRICKSTERS+"entrance","north");
 add_exit(TRICKSTERS+"hall","southeast");

 create_skill_raise();
 set_up_skills();
}

void init()
{
 init_skill_raise();
 ::init();
}

int sk_improve(string str)
{
 if(!(SERVER)->query_member(TP->query_name()))
  {
   write("Only tricksters can train here!\n");
   return 1;
  }

 if((SERVER)->query_restricted(TP->query_name()))
  {
   write("You have been restricted from training!\n");
   return 1;
  }

 return ::sk_improve(str);
}

