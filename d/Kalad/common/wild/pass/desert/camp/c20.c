inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define BELD "/d/Kalad/common/wild/pass/npc/bed_eld"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Inside the central tent");
   set_long("You are now deep within the Sheik's tent. The unaddorned passages "+
      "head off to the east, and to the south. In the southeast is a heavy red "+
      "blanket, which seems to be blocking that way. The floor is covered by "+
      "an elegant red carpet.\n");
   add_item(({"sheik's tent","tent"}),"It is what you are inside of!\n");
   add_item(({"unaddorned passages","unaddorned passage","passages","passage"}),
      "The canvas walls of the tent form passageways here within the tent, "+
      "leading to the east and south.\n");
   add_item(({"canvas walls","canvas wall","walls","wall"}),"Made from sturdy "+
      "camel hair, it forms an effective barrier against the harsh wind of the "+
      "Great Kalad Waste.\n");
   add_item(({"heavy red blanket","heavy blanket","red blanket","blanket"}),
      "A large wool-fibered covering that blocks the way southeast. It "+
      "has been dyed a deep crimson red, and an image of a red sun has "+
      "been sewn onto it.\n");
   add_item(({"floor"}),"Other than the carpet that covers it, it is "+
      "nothing but sand.\n");
   add_item(({"sand"}),"Made up of numerous small particles, its what "+
      "you would expect sand would look like.\n");
   add_item(({"elegant red carpet","elegant carpet","red carpet","carpet"}),
      "A wonderful floor rug that has been dyed an exotic burgundy red in "+
      "color. It nearly covers the entire floor, all but covering the sand that "+
      "it is composed of.\n");
   add_exit(CPASS(desert/camp/c19),"east",0,-1);
   add_exit(CPASS(desert/camp/c26),"southeast","@@move",-1);
   add_exit(CPASS(desert/camp/c25),"south",0,-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/bed_ueld");
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A Bedellin Elder emerges from deeper in the tent.\n");
   }
   if(!ob2)
      {
      ob2 = clone_object(BELD);
      ob2 -> my_stuff();
      ob2 -> move_living("M",TO);
      tell_room(TO,"A second Bedellin Elder arrives from somewhere deeper in the tent.\n");
   }
   if(!ob3)
      {
      ob3 = clone_object(BELD);
      ob3 -> my_stuff();
      ob3 -> move_living("M",TO);
      tell_room(TO,"Another Bedellin Elder arrives, right after the first two.\n");
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
   }
}
move()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_adj() == "bedellin"){
         pres = 1;
       }
   }
   if(pres == 1){
      write("The bedellin elder prevents you from going southeast.\n");
      say(QCTNAME(TP) + " tries to go southeast, but is prevented by the bedellin elder.\n");
   }
   return pres;
}
