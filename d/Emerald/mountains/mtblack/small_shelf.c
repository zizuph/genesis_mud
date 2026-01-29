inherit "/std/room";

#include "/d/Emerald/defs.h";

void create_room() {
  set_short("Small shelf");
  set_long("You are standing upon a narrow shelf on the southern "+
           "side of Mount Black.  You cannot see the sky above you "+
           "from this point as it is completely enshrouded in mists."+
           "  The ground itself is moist from the mist and is "+
           "covered is small lichens.  Far below you can see the "+
           "valley floor covered in trees.  A crack in the side of "+
           "the mountain leads back into a cave to the north.\n");
  add_item("lichen", "It's extremely moist from the mist and seems "+
           "quite slippery.  You had better watch your step.\n");
  add_item("mist", "The mist is pure white in color and completely "+
           "obscures your vision of the sky above you and the peak "+
           "of the mountain.  It has also coated everything in a "+
           "slick layer of dew.\n");
  add_exit(MBLACK_DIR + "cave_middle", "north");
}
