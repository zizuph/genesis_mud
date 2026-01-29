inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
int pres,i;
object *ob;
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_I_LIGHT,0);
   INSIDE;
   set_short("Within the ruined tower");
   set_long("This level of the ruined tower must have once been a "+
      "grand library, judging from the great piles of ruined books and "+
      "bookshelves lying about. The stench of rotting flesh pervades "+
      "your nostrils. A nearly ruined staircase heads both up and down "+
      "here, while dust and sand covers everything in a thick layer.\n");
   add_item(({"great piles","piles","pile","ruined books","books","book","bookshelves","bookshelf"}),
      "Waist-high mounds of partially burned books and bookshelves fill "+
      "the room. Strangely enough, only the smell of rotten flesh reaches your "+
      "nose.\n");
   add_item(({"ruined staircase","staircase"}),"A crumbling set of "+
      "stone stesp leading both up and down from this level of the tower.\n");
   add_item(({"dust","sand"}),"It lies in a thick layer over everything "+
      "in the room.\n");
   add_exit(CPASS(desert/sand/r4),"up",0,-1);
   add_exit(CPASS(desert/sand/r2),"down","@@check",-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/rt_gzombie));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A giant zombie seems to arrive from nowhere.\n");
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/rt_ozombie));
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      tell_room(TO,"An ogre zombie seems to arrive from nowhere.\n");
   }
}
check()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for (i = 0; i < sizeof(ob); i++)
   {
      if (ob[i]->query_name() == "Zombie")
         {
         pres = 1;
        }
   }
   if (pres == 1)
      {
      write("You try to go down but are stopped by a zombie!\n");
      say(QCTNAME(TP) + " tried to go but is stopped by a zombie!\n");
   }
   return pres;
}
