/*
w17.c is E
w19.c is NW
w21.c is SW
*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

static int meat_here;

void
reset_room()
{
  
  meat_here = 1;
  
}

void
create_room()
{
  set_short("tunnel fork");

  set_long(
	   "The large western tunnel forks here, branching off to the\n" +
	   "northwest and southwest, and returning eastward.  The musty,\n" +
	   "underground smell added by the stench from big pile of refuse\n" +
	   "is quite strong here, filling your nostrils with its\n" +
	   "unpleasantness.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");    

  add_item ( ({"pile", "refuse", "pile of refuse"}),
	    "Everything the two ogre families have discarded lies here\n" +
	    "to the kids' pleasure.\n");
  
  add_exit(L4 + "w19", "northwest",0);
  add_exit(L4 + "w21", "southwest",0);
  add_exit(L4 + "w17", "east",0);

  add_prop (OBJ_S_SEARCH_FUN, "search_fun");
  add_prop(ROOM_I_LIGHT,0);
  IN;
  add_npc(MON +"ogre_kid", 1, &->equip_me());
  reset_room();
}

string
search_fun(object tp, string what)
{
  if (meat_here && (what == "pile" || what == "refuse"))
    {
      clone_object(OBJ + "r_meat")->move(this_object());
      meat_here = 0;
      return "You find a piece of rotten meat in the pile of refuse!\n";
    }
  return "Your search reveals nothing.\n";
}





