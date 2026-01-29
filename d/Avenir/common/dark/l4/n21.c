// file name: ~Avenir/common/dark/l4/n21.c
// creator(s):
// revision history:
//   - 'exa web' -=Denis /Jan, 95
// purpose:
// note: by 'exa web' a player can get a small piece of source sometimes.
// bug(s):
// todo:

/*
n22.c is NE
n20.c is E
n27.c is W
*/

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/common/dark/l3/l3_defs.h"

inherit "/std/room";
inherit SOURCE_CHECKER;

void
reset_room()
{
  if (!present ("fur", this_object()))
    clone_object (OBJ + "d_fur")->move(this_object());
}

void
create_room()
{
  set_short("dirty tunnel");
  set_long("The rough, dirty stone passageway continues here, "+
	   "going from east to west, while "+
	   "a nearly-hidden hole leads northeast.  Cobwebs hang "+
	   "everywhere here, making it difficult to see.\n");
  
  add_exit(L4 + "n20","east",0);
  add_exit(L4 + "n27","west",0);
  add_exit(L4 + "n22","northeast","@@do_web");
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
  
  add_item("hole","It leads northeast.\n");
  
  AI(({"cobweb","cobwebs"}),"@@exa_fun");
  
  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
	   "passageway"}), "Very uninteresting stone.\n");
  can_contain_source=1;
  reset_room();
}
// Added by Tep for creepiness factor
int
do_web()
{
    if (!random(3))
    {
	write("You break through the cobwebs.\n" +
	  "A shiver runs up your spine as they brush against " +
	  "your face. This place makes your skin crawl.\n\n");
	this_player()->add_panic(100);
    } 
  return 0;
}

string
exa_fun()
{
  if(find_source(TP,2))
    return "You notice a small glowing piece in the webs... \n"+
      "Then you move your hand and reach it. Cleaning it from "+
	"the small remains of \nthe web, you wonder if spiders "+
	  "like gathering jewels in their webs.\n";
  
  else
    return "The cobwebs hang down in your face tickling your skin.\n";
}
