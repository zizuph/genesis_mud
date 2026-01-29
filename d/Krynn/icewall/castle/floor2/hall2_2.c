#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

create_icewall_room()
{
   set_short("Hallway On Second Floor");
   set_long(BS(
         "The corridor here runs north and south.  The floorboards creak slightly"
         + " under your weight.",75));
   
   add_exit(ICE_CAST2_R + "hall4_2.c", "north");
   add_exit(ICE_CAST2_R + "main_hall.c", "south");
}
