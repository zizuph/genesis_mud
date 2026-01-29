inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
reset_room()
{
  object glove;
  
  if (!present ("glove", this_object()))
    {
      glove = clone_object (OBJ + "l_glove");
      glove->move (this_object());
    }
}

void
create_room()
{
  set_short("small dirty tunnel");
  
  set_long(
    "The small, dirty tunnel turns here, heading northwest through a\n" +
    "thick wall of cobwebs, and also to the south. Two rows of support\n" +
    "shafts keep the ceiling from falling on your head.\n");
  
  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");
  
  AI(({"cobweb","cobwebs", "web"}),"The cobwebs hang down in your " +
   "face, tickling your skin.\n");

  AI(({"shafts", "supports"}),
     "They are wooden logs and iron poles stuck between the ceiling and\n" +
     "the walls preventing loose rocks from falling on your head.\n");
  
  AE(L4+"n22","south",0,DIRT);
  AE(L4+"n24","northwest","@@do_web",DIRT);
  
  add_prop(ROOM_I_LIGHT,0);
  IN;
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
	this_player()->add_panic(20);
    } 
  return 0;
}
