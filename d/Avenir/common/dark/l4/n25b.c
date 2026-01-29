/*
n26.c is NW
n24.c is SE
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

create_room()
{
  set_short("Small dirty stairwell");
  set_long("The small, rocky stairwall is a midway point between the second "+
      "level of the utterdark and the lower fourth level. The stone is dark "+
      "and uninteresting.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");
  
  AI(({"cobweb","cobwebs"}),"The cobwebs hang down in your " +
   "face, tickling your skin.\n");
  

  AE(L2+"n10","up");
  AE(L4+"n25", "down");
  add_prop(ROOM_I_LIGHT,0);
  IN;
}

