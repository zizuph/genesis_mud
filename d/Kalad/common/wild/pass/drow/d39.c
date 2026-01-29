inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A street within the drow city of Undraeth");
   set_long("Huge structures of rock known as stalagmites and "+
      "stalactites rise far above you, having been magically enchanted by "+
      "the resident populace into the graceful structures before you now. "+
      "The warmth of the air here is comforting, though it is stagnant and "+
      "stale-smelling. "+
      "A compound lies to the east, just off the street. "+
      "The street takes a slight bend here, veering to the south from the "+
      "northeast.\n");
   add_item(({"gigantic structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"compound"}),
      "A collection of stalagmites that have been formed into a building. "+
      "A sign hangs before it.\n");
   add_item("sign","Several words written in glowing faerie fire are visible "+
      "upon it.\n");
   add_cmd_item("sign","read",
      "It reads: The Sausage House\n");
   add_exit(CPASS(drow/d44),"northeast");
   add_exit(CPASS(drow/shop/sausage),"east","@@block",-1,-1);
   add_exit(CPASS(drow/d40),"south");
   set_noshow_obvious(1);
}
block()
{
   write("Alas, it appears as if the sausage house is closed.\n");
   return 1;
}
