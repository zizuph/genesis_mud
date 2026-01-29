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
      "surrounds you. A small road leads off to the south to a "+
      "rather large and fancy estate. Further to the southeast, "+
      "you see a small castle.\n");
    add_item("castle","It rises above the trees and buildings. "+
      "It must be the famous castle of the high-lord.\n");
    add_item("estate","A very huge and finely decorated house "+
      "with many green-black banners and flags.\n");
    add_exit(NOBLE(wayfarer/s3),"west",0,0,-1);
    add_exit(NOBLE(wayfarer/s5),"east",0,0,-1);
    add_exit(NOBLE(road/r14),"south",0,0,-1);
}

