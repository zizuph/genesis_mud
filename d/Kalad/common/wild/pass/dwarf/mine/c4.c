inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
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
      "floor and ceiling, with some traces of large spider webs "+
      "hanging inbetween them. Small drops of water drips down from "+
      "them as it has done for hundreds of years. The air is cold "+
      "and filled with moisture. The path twists itself inbetween "+
      "the stalagmites to southwest, southeast, northeast and "+
      "northwest.\n");
   add_item(({"web","webs"}),
      "It is a woven, silky network spun by spiders to "+
      "serve as nests and as traps for prey. These looks fairly "+
      "large, and feels sticky to the touch.\n");
   add_item(({"stalagmite","stalagmites","stalactite","stalactites"}),
      "The stalactites is shaped like icicles, hanging from the "+
      "roof of the cave in different lenghts. Just like the stalactites "+
      "the stalagmites are formed from the dripping of water saturated "+
      "with calcium, but stands on the floor like small cone-formed towers.\n");

   add_exit(CPASS(dwarf/mine/c6),"northwest","@@web@@",3);
   add_exit(CPASS(dwarf/mine/c3),"southwest",0,3);
   add_exit(CPASS(dwarf/mine/c5),"northeast","@@web@@",3);
   add_exit(CPASS(dwarf/mine/c2),"southeast",0,3);

   set_noshow_obvious(1);
}
web()
{
   if(TP->query_base_stat(SS_STR)<30)
   {
      write("You cannot get through! The cobweb is too strong for "+
         "you to penetrate it.\n");
      return 1;
   }
   write("You tear apart the cobweb and pass through it.\n");
   return 0;
}
