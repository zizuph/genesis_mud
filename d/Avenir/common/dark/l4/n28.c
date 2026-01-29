/*
n27.c is E
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
reset_room()
{
  if (!present ("ring", this_object()))
    clone_object (OBJ + "s_ring")->move(this_object());
}

void
create_room()
{
  set_short("huge chamber");
  set_long("You stand in a huge chamber with a high, vaulted ceiling. "
   +" After the dirt and dust of the tunnels, this square-cut, well-"
   +"kept area seems foreign.  A strange, rectangular altar sits in "
   +"the center of the room, and burnt-out torches line the walls.\n");             

  add_item(({"torch","torches"}), 
	   "The torches are securely fastened to the walls, and appear to " +
	   "have been recently extinguished.\n");
  
  add_item("altar","The altar is dark stone, cut with precise square " +
	   "corners.  It appears to be smeared with blood.\n");
  
  AI("ceiling", "It is a good seven man-lengths above you.\n");
  
  AI(({"blood","smear","smears"}), 
     "The blood looks....a little too fresh for your comfort.\n");    
  
  add_exit(L4 + "n27", "east",0);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  reset_room();
}

void
init()
{
  ::init();
  add_action ("do_pray", "pray");
}

int
do_pray(string str)
{
  object tp;
  
  notify_fail ("Pray where?\n");
  if (!str || (str != "before altar" && str != "at altar"))
    return 0;

  tp = this_player();
  write ("You kneel at the strange altar and pray to the unknown gods.\n");
  say (QCTNAME(tp) + " kneels at the altar and prays silently.\n");
  return 1;
}
