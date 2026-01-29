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
      "surround you. You are at a T intersection here, where a "+
      "small clean road leading south meets Wayfarer's. To "+
      "the north you also see a fine looking pub. There is a sign "+
      "above it. Further to the southeast, "+
      "you see a small castle.\n");
    add_cmd_item("sign","read","Royal Pub.\n");
    add_item("sign","It has golden words on it.\n");
    add_item("pub","A white bricked building with fine oak doors.\n");
    add_item("castle","It rises above the trees and buildings. "+
      "It must be the famous castle of the high-lord.\n");
    add_item("estate","A very huge and finely decorated house "+
      "with many green-black banners and flags.\n");
    add_exit(NOBLE(wayfarer/s4),"west",0,0,-1);
    add_exit(NOBLE(wayfarer/s6),"east",0,0,-1);
    add_exit(NOBLE(road/r7),"south",0,0,-1);
    add_exit(NOBLE(pub),"north",0,0,-1);
}

