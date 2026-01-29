// file name:    n3
// creator(s):   Cirion, April 1996
// last update:
// purpose:      Tunnel for the newbie area.
// note:         
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/room";
#include "outpath.h"
  
void create_room()
{
  set_short("dank tunnel");
  set_long("Thick shadows play on the walls of the tunnel, "
       +"and the moisture that drips from the rocks "
       +"glimmers in the light. A strong wind blowing from "
       +"the south makes an eerie whistling noise as "
       +"it passes along the jagged rocks. The tunnel "
       +"turns from the south to the northeast.\n");

  add_item(({"wall","walls","rock"}),"The rock walls of this "
    +"tunnel are craggy and rough-hewn, their cold surface "
    +"glistening with moisture and latticed with numerous "
    +"shadows.\n");
  add_item(({"floor","ground"}),"The ground is cold and "
    +"rough, making your footing treacherous.\n");
  add_item(({"ceiling","roof"}),"The ceiling of the tunnel "
    +"is hidden in shadows.\n");
  add_item(({"shadow","shadows","darkness"}),"The shadows are "
    +"everywhere.\n");
  add_item(({"mist","south"}),"To the south is only darkness "
    +"out of which a cold wind blows.\n");

  IN;
  IN_IN;
  remove_prop(ROOM_I_LIGHT);

  add_exit(OUTPATH+"n2", "south");
  add_exit(OUTPATH+"n4", "northeast");
}
