/*
w14.c is E
*/

inherit "/d/Avenir/inherit/room";

#include "/d/Avenir/common/dark/dark.h"


void
create_domain_room()
{
  set_short("Dark tunnel");
  set_long("More tunnel. The stone is unremarkable wherever you look. "
      +"You smell ogres and dust.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
	 "passageway"}), "Very uninteresting stone.\n");    
  AI("dust", "It is thick on the floor. Your footsteps stir " +
     "it up and cloud the air.\n");
  add_exit(L4+"w14","east",0,DUST);
  add_exit(L4+"n31","west");
  add_prop(ROOM_I_LIGHT,0);
  IN;
}

