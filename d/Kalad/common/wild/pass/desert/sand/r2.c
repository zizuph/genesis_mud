inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
int pres,i;
object *ob;
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_I_LIGHT,0);
   INSIDE;
   set_short("Within the ruined tower");
   set_long("This level of the ruined tower appears to have once been "+
      "a guest area of sorts. The pervading smell of death and decay fills "+
      "the room with its sickening stench. Scattered around the room are "+
      "the fragmented and ruined "+
      "remains of chests, beds and mirrors. Covering everthing is a thin "+
      "film of sand and dust. A nearly ruined staircase leads both up and "+
      "down from here.\n");
   add_item(({"fragmented remains","remains","chests","chest","beds","bed","mirrors","mirror"}),
      "The shattered remnants of furniture litter this level of the tower, "+
      "covered in dust and sand.\n");
   add_item(({"thin film","film","dust","sand"}),"It lies in piles in "+
      "some places, but for the most part merely covers everything like a "+
      "blanket.\n");
   add_item(({"ruined staircase","staircase"}),
      "A crumbling stone set of stairs that nonetheless is still serviceable, "+
      "though barely.\n");
   add_exit(CPASS(desert/sand/r3),"up",0,-1);
   add_exit(CPASS(desert/sand/r1),"down","@@check",-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/rt_wight));
      ob1 -> move_living("M",TO);
      tell_room(TO,"A ghastly creature suddenly appears before you.\n");
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
      if(ob[i]->query_name() == "Wight")
         {
         pres = 1;
        }
   }
   if (pres == 1)
      {
      write("You try to go down but are stopped by the ghastly wight!\n");
      say(QCTNAME(TP) + " tried to go down but is stopped by the ghastly wight!\n");
   }
   return pres;
}
