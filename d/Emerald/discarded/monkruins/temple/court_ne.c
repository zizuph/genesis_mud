inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void create_room()
{
    object door;
 
    set_short("Northeast corner of Courtyard");
	set_long("   You are standing in the northeastern corner of the " +
      "courtyard. Only a few figures of monks are "+
      "seen around, since due to the hot sun the place is quite "+
      "warm. Your eye is attracted to a big carving on the inner "+
      "side of the courtyard's wall. To your east, there is a door "+
	"leading into a large building. Could it be a monestary?\n\n");

    add_exit(TEMPLE_DIR + "court_nw", "west", 0);
    add_exit(TEMPLE_DIR + "court_e", "south", 0);

    door=clone_object(TEMPLE_DIR + "doors/door2_a");
    door->move(this_object());
 
    add_item("building", "It's large. To your east, there is a "+
              "door leading into it.\n");
    add_item("carving","The carving depicts some god-like "+
              "figure, standing in the doorframe. The shining "+
              "is coming from its hands, body, face, and "+
              "especially from its eyes. Looking at it you "+
              "guess it was an elf before, but it really isn't one "+
              "anymore. You look closely, but don't find any clue "+
              "who was the master who carved this.\n");
}
