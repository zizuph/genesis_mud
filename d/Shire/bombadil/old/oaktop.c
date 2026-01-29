inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"

create_room()
{
    set_short("Treetop");
    set_long(break_string(
	  "You have almost climbed to the top of this large oak tree. "
        + "South you only see a green roof of leaves stretching out as far "
        + "as the eye can see. "
        + "To the east you see the enormous forests between here and Bree. "
        + "The tree has lots of traces of bird activities.\n",70));

    add_item("traces",break_string(
	  "Birds seems to have been active in this tree. You see all kinds "
	+ "of small feather and broken twigs that can be used to build "
	+ "birdnests.\n",70));

    add_exit(DOWNS_DIR + "oak1", "down");

    reset_room();
}

reset_room()
{
   if (!present("mushroom"))
      clone_object(HERB_DIR + "treemushroom")->move(this_object());
}
