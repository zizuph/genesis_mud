inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the drow city of Undraeth");
   set_long("Gigantic structures of rock known as stalagmites and "+
      "stalactites tower far above you, having been magically altered by "+
      "the native population into the impressive structures before you now. "+
      "The air here is warm, yet is quite stagnant and oppressive. It is "+
      "almost uncanny in its immobility, for the air here is as dead as can "+
      "be. "+
      "The sheer face of a cavern wall rises in the west, its top lying in "+
      "darkness. "+
      "In the east lies a large stalagmite compound. "+
      "This street snakes its way to the north and southwest.\n");
   add_item(({"gigantic structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"cavern wall","wall"}),"A sheer face of dark black stone "+
      "whose periphery is lost in darkness.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"large stalagmite compound","large compound","stalagmite compound","compound"}),
      "A massive gathering of stalagmites, clustered around one another "+
      "they seem to form a structure reminiscent of castles on the surface "+
      "world.\n");
   add_exit(CPASS(drow/d9),"north");
   add_exit(CPASS(drow/house5/entrance),"east");
   add_exit(CPASS(drow/d5),"southwest");
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/rand_drow));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A single drow emerges from the gloomy darkness of the "+
         "surrounding city.\n");
   }
}
