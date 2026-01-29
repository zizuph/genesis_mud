inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
create_room()
{
  set_short("small dirty tunnel");
  set_long(
    "You are in a small, low-ceilinged tunnel. The ceiling appears to be\n" +
    "in a bad shape and only wooden and iron supports prevent it from\n" +
    "crashing. Cobwebs are everywhere here, and the dust hangs so heavily\n" +
    "as to make breathing difficult. The tunnel leads to the southwest,\n" +
    "into a larger passageway, and northward, into deep darkness.\n");
  
  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
	 "passageway"}), "Very uninteresting stone.\n");
  
  AI("dust", "It is thick on the floor. Your footsteps stir " +
     "it up and cloud the air.\n");
  
  AI(({"cobweb","cobwebs"}),"The cobwebs hang down in your " +
     "face, tickling your skin.\n");
  
  AI("supports",
  "These wooden logs and iron shafts supporting the ceiling were left here\n"+
  "by the tunnel builders.\n");
    
  AE(L4+"n21","southwest",0,DIRT);
  AE(L4+"n23","north",0,DIRT);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
}
