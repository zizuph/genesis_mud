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
      "The air is fresh and clean, and various beautiful plant life "+
      "surrounds you. A large estate rises off to your south, while "+
      "the boulevard continues to your east and west.\n");
    add_item("estate","A very huge and finely decorated house "+
      "with many green-black banners and flags.\n");
    add_exit(NOBLE(wayfarer/s2),"west",0,0,-1);
    add_exit(NOBLE(wayfarer/s4),"east",0,0,-1);
}

