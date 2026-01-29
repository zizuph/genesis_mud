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
      "floor and ceiling, with some traces of old spider webs "+
      "hanging inbetween them. Small drops of water drips down from "+
      "them as it has done for hundreds of years. The air is cold "+
      "and filled with moisture. The path twists itself inbetween "+
      "the stalagmites to southeast and "+
      "northeast.\n");
   add_item(({"web","webs"}),
      "It is a woven, silky network spun by spiders to "+
      "serve as nests and as traps for prey. These looks fairly "+
      "old, but still feels sticky to the touch.\n");
   add_item(({"stalagmite","stalagmites","stalactite","stalactites"}),
      "The stalactites is shaped like icicles, hanging from the "+
      "roof of the cave in different lenghts. Just like the stalactites "+
      "the stalagmites are formed from the dripping of water saturated "+
      "with calcium, but stands on the floor like small cone-formed towers.\n");

   add_exit(CPASS(dwarf/mine/c4),"northeast",0,3);
   add_exit(CPASS(dwarf/mine/c1),"southeast",0,3);

   set_noshow_obvious(1);
   set_alarm(0.0,0.0,"reset_room");
}
reset_room()
{
   if(!objectp(ob1))
   {
      ob1=clone_object(CPASS(dwarf/npc/spider));
      ob1->move_living("M",TO);
      tell_room(TO,"A spider comes crawling out from the shadows.\n");
   }
}
