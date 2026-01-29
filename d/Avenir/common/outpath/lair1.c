// file name:    lair1.c
// creator(s):   Cirion, April 1996
// last update:
// purpose:      Lair where there are maggot eggs
// note:         
// bug(s):
// to-do: 
#pragma strict_types

inherit "/std/room";
#include "outpath.h"
  
void reset_room()
{
  int   i;

  if(present("egg", TO))
    return;

  tell_room(TO, "Some slimy white eggs roll into the room from "
      +"the north.\n");
  for(i=0;i<random(10) + 10;i++)
    clone_object(OBJ+"egg")->move(TO, 1);
}

void create_room()
{
  set_short("slimy cavern");
  set_long("This is the southern end of a small cavern. The "
     +"ceiling is very low here, and everything is covered in "
     +"a thin film of translucent white slime. Moisture glistens "
     +"on the walls, occasionally dripping down to the floor to "
     +"mingle with the filth, making it extremely slippery.\n");

  ACI(({"","air","here"}),({"smell","sniff"}),"The air smells "
    +"terrible, like the decay of some ancient beast.\n");

  add_item(({"wall","walls","cave","cavern"}),"The walls of the "
    +"cavern are smooth and wet.\n");
  add_item(({"floor","ground"}),"It is slippery and wet, covered "
    +"in a sticky white slime.\n");
  add_item(({"ceiling","roof"}),"It is very low and smooth.\n");

  IN;
  IN_IN;
  remove_prop(ROOM_I_LIGHT);

  add_exit(OUTPATH+"n4", "southeast");
  add_exit(OUTPATH+"lair2", "north");

  reset_room();
}
