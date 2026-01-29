inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A street within the drow city of Undraeth");
   set_long("A great many stalagmites and stalactites fill your field "+
      "of view. These immense structures of rock rise far above you, having "+
      "been structurally enhanced by the populace of the city into the "+
      "strangely beautiful structures before you. "+
      "The air around you is warm from the presence of so many living beings in "+
      "the area. It is also quite stale and stagnant, due to its presence far "+
      "below the fresh air of the surface. "+
      "A large stalagmite compound lies to the north. "+
      "The street you are travelling on runs straight to the west, towards "+
      "the bazaar and east, towards the pit of Undraeth.\n");
   add_item(({"immense structures","structures","structure","rock","stalagmites","stalagmite","stalactites","stalactite"}),
      "Monumental in their size, these huge rock formations provide living "+
      "space for the many inhabitants of this city.\n");
   add_item(({"streets","street"}),"The perfectly flat and smooth "+
      "structures seem to bend and twist in many directions, a rather "+
      "chaotic road design as compared to many surface cities. Yet unlike "+
      "them, not the slightest bit of rubbish litters these streets.\n");
   add_item(({"large stalagmite compound","large compound","stalagmite compound","compound"}),
      "A huge structure crafted from pre-existing stalagmites of "+
      "immense proportions. So ingenious is its melding, that the individual "+
      "stalagmites have been combined to form an imposing fortress.\n");
   add_exit(CPASS(drow/bazaar/b3),"west");
   add_exit(CPASS(drow/house3/entrance),"north","@@block");
   add_exit(CPASS(drow/d40),"east");
   set_noshow_obvious(1);
}
block()
{
   write("A magic mouth suddenly appears from a nearby stalagmite and shouts:\n"+
      "House Eilservs is off limits!\n"+
      "It then abruptly disappears.\n");
   say("A magic mouth suddenly appears from a nearby stalagmite and shouts:\n"+
      "House Eilservs is off limits!\n"+
      "It then abruptly disappears.\n");
   write("It would appear there is no way in, for now.\n");
   return 1;
}
