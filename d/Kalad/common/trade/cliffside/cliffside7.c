inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
/* modified by Antharanos */
   void
create_room()
{
   set_short("Cliffside Road");
   set_long("The road to the west nears the central district. To your "
      +"south a house with smoke billowing from a chimney stands. To "
      +"the north is a long, narrow alleyway that looks ideal for a "
      +"thief to be hiding in.\n");
   add_item(({"house"}),"The house has smoke pouring out of its chimney "
      +"and loud noises come from inside.\n");
   add_item(({"alley","alleyway"}),"The alley is narrow and dark, you "
      +"better be careful!\n");
   add_exit(TRADE(cliffside/cliffside6),"east");
   add_exit(TRADE(cliffside/cliffside8),"west");
   add_exit(TRADE(cliffside/bsmith),"south");
   add_exit(TRADE(cc3),"north");
   add_item(({"street","streets"}),"There is less trash and other "
      +"refuse lying in the street. "
      +"The streets are also broader.\n");
   add_item(({"road","roads","intersection"}),"This is a plain road, "
      +"not at all interesting in the least. It is made of worn "
      +"stone, and is dirty.\n");
   add_item(({"homes","home"}),"They are small old "
      +"houses belonging to the lower classed tradesman of Kabal.\n");
   add_item(({"shops","shop"}),"They are small businesses run by the "
      +"lower-classed people.\n");
   hear_bell = 2;
}
