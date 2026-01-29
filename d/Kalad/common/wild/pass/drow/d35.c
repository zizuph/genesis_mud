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
   set_long("Numerous stalagmites and stalactites encompass your field "+
      "of view. These immense structures of rock stretch far above the "+
      "ground, having been magically enchanted by the city's populace into "+
      "the incredible structures before you now. "+
      "Due to the many living beings dwelling within the city, the air is "+
      "comfortably warm, though it is somewhat oppressive and stagnant "+
      "because of the distance to the surface, where fresh air lies. "+
      "The sheer face of a cavern wall rises in the north, its top lying in "+
      "darkness, while to the south is an immense chasm. "+
      "The street runs straight and true here, like a knife into an unsuspecting back, "+
      "heading to the southwest and northeast.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"cavern wall","wall"}),"A sheer face of dark black stone "+
      "whose periphery is lost in darkness.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"immense chasm","chasm"}),
      "A great, yawning rent within the surface of this cavern, it appears "+
      "nearly bottomless.\n");
   add_exit(CPASS(drow/d38),"northeast");
   add_exit(CPASS(drow/d30),"southwest");
   add_exit(CPASS(drow/chasm/c2),"south","@@block");
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
block()
{
   write("That would be quite foolish, as it would lead to your "+
      "untimely death.\n");
   return 1;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/b_w_spider));
      ob1 -> move_living("M",TO);
      tell_room(TO,"Something shifts in the surrounding darkness.\n");
   }
}
