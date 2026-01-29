inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <thanardefs.h>
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("The private chamber of the Thanarian guild");
   set_long("This large oval chamber is the private meeting area of the "+
      "Thanarians. Within these vaulted walls of black marble, members may "+
      "meet and discuss topics of interest to them, without fear of "+
      "interruption from non-believers, for only the faithful of Thanar may "+
      "enter this place. A ring of black stone benches surrounds the center "+
      "of the room, where an obsidian board lies.\n");
   add_item(({"large oval chamber","large chamber","oval chamber","chamber","private chamber","meeting area","area"}),
      "An oval room where members of the Thanarians may meet and discuss "+
      "topics of importance.\n");
   add_item(({"vaulted walls","walls","vaulted wall","wall"}),
      "Constructed from black marble, the eerily dark rock seems to reflect "+
      "the dark nature of the individuals residing here.\n");
   add_item(({"floor","ceiling"}),
      "It is constructed of the same black marble the rest of the chamber has "+
      "been.\n");
   add_item(({"black marble","marble"}),
      "A stone the color of darkness itself.\n");
   add_item(({"ring"}),
      "You mean the benches?\n");
   add_item(({"black stone benches","black benches","stone benches","benches","benches","bench"}),
      "Each and every bench is identical in its flawless design, constructed "+
      "from a stone that can only be described as darkness itself. They form "+
      "a ring around the obsidian board that lies at the center of this chamber.\n");
   add_item(({"center"}),
      "An obsidian board lies there.\n");
   add_exit(THANAR(joinroom),"west",0,-1);
   clone_object(THANAR(private_board))->move(TO);
}
