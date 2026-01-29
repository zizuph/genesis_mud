/*
n26.c is NW
n24.c is SE
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

create_room()
{
  set_short("Small dirty tunnel");
  set_long("The small, rocky tunnel continues here, going northwest and "
    +"southeast through a mass of tangled cobwebs. There is a rough "
    +"set of stairs carved into the wall leading upwards into deep "
    +"darkness. \n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");
  AI(({"stairs", "set of stairs", "stairwell", "wall"}), "There is "
      +"a very crude set of stairs carved into the wall.\n");
  AI(({"cobweb","cobwebs"}),"The cobwebs hang down in your " +
   "face, tickling your skin.\n");
  
  AE(L4+"n24","southeast");
  AE(L4+"n26","northwest");
  AE(L4+"n25b", "up");
  add_prop(ROOM_I_LIGHT,0);
  IN;
}

