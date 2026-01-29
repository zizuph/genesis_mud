/*
n30.c is NE
L3/ec3.c is UP
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
reset_room()
{
  if (!present ("stick", this_object()))
    clone_object (OBJ + "w_stick")->move(this_object());
}

void
create_room()
{
  set_short("rocky tunnel");
  set_long("The dusty tunnel looks like it comes to a sudden halt in "
+"a rockfall but just when you are about to turn around you notice "
+"a bend in the tunnel. You can go northeast or east from here. "
+"\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
       "passageway"}), "Very uninteresting stone.\n");   
  add_item(({"rockfall", "rock", "rocks", "rubble"}), 
  "A part of the tunnel has collapsed here, partially blocking it "
+"with large, immovable rocks.\n");  

  add_exit(L4 + "n30","northeast",0);
  add_exit(L4 + "w15","east",0);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  
  reset_room();
}

