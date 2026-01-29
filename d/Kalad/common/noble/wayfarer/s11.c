inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* By Sarr of Kalad */

void
create_room()
{
    ::create_room();
    set_short("Along Wayfarer's Boulevard");
    set_long("You are travelling along Wayfarer's Boulevard in "+
      "the Noble district. The Boulevard here is very well kept and "+
      "clean, as opposed to its condition in the Caravan district. "+
      "You are approching the intersection of Wayfarer and High "+
      "Streets. A castle rises off to your southwest.\n");
    add_item("guards","Many guards patrol the top.\n");
    add_item("flags","The flags of the high-lord.\n");
    add_item("towers","There are four, one on each corner.\n");
    add_item("castle","It rises above the trees and buildings. "+
      "It must be the famous castle of the high-lord.\n");
    add_exit(NOBLE(wayfarer/s10),"west",0,0,-1);
    add_exit(CVAN(high-wayfar),"east",0,0,-1);
}

