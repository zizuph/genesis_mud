inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   DIRTY(2);
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within some cave close to Underhome");
   set_long("This cave is natural, being excavated in the "+
      "hard rock by flowing water. "+
      "Large stalagmites and stalactites covers the cave on the "+
      "floor and ceiling, with a large, sticky spider web "+
      "hanging inbetween them. Small drops of water drips down from "+
      "them as it has done for hundreds of years. The air is cold "+
      "and filled with moisture. The path twists itself inbetween "+
      "the stalagmites to southwest, southeast, and "+
      "north.\n");
   add_item(({"web","webs"}),
      "It is a woven, silky network spun by spiders to "+
      "serve as nests and as traps for prey. This one looks very "+
      "large, and feels very sticky to the touch. It would be your "+
      "death if you got stuck in them.\n");
   add_item(({"stalagmite","stalagmites","stalactite","stalactites"}),
      "The stalactites is shaped like icicles, hanging from the "+
      "roof of the cave in different lenghts. Just like the stalactites "+
      "the stalagmites are formed from the dripping of water saturated "+
      "with calcium, but stands on the floor like small cone-formed towers.\n");

   add_exit(CPASS(dwarf/mine/c8),"north","@@web@@",3);
   add_exit(CPASS(dwarf/mine/c6),"southwest",0,3);
   add_exit(CPASS(dwarf/mine/c5),"southeast",0,3);

   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}
web()
{
   if(objectp(ob1) && CAN_SEE(ob1,TP))
   {
      write("The enormous spider stands in the way!\n");
      return 1;
   }
   if(TP->query_base_stat(SS_STR)<50)
   {
      write("You cannot get through! The cobweb is too strong for "+
         "you to penetrate it.\n");
      return 1;
   }
   write("You tear apart the cobweb and pass through it.\n");
   return 0;
}
reset_room()
{
   if(!objectp(ob1))
   {
      ob1=clone_object(CPASS(dwarf/npc/big_spider));
      ob1->move_living("M",TO);
      tell_room(TO,"An enormous spider comes crawling down from the center "+
         "of the cobweb. It looks like it is ready to feed ... on you!\n");
   }
}
