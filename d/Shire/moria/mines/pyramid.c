#include "defs.h"

CONSTRUCT_ROOM {
    set_short("This is the Pyramid");
    set_long("This is the Pyramid. It's a high-ceilinged room with pointed "+
	     "roof, thereby making the characteristic form of this room. "+
	     "Paintings with intricate patterns in psychedelic colours "+
	     "decorate the walls and the ceiling. You can hear tones of "+
	     "music arriving from a distance. To the north, there is a "+
	     "difficult opening over some blocks of stone. To the east, "+
	     "there is a passage with a pentagonal cross-section covered "+
	     "with white garland. Quite odd really...\n");
    add_item(({"room","roof","form"}),"It is pyramidal.");
    add_item(({"paintings","wall","walls","ceiling"}),
	     "The paintings seem kind of hysterical, lots of colours in a "+
	     "chaotic fashion.");
    add_item(({"tones","music"}),
	     "If you listen carefully to it, you might be able to figure out "+
	     "the meaning.");
    add_item(({"opening","blocks","stone"}),
	     "That was where you came from. If you can get in, you can get "+
	     "out.");
    add_item(({"passage","garland"}),
	     "I don't think we shall disturb the oddity of this room by "+
	     "removing the garland. Obviously, strange forces work around "+
	     "here.");
    EXIT("rattrap","east");
    EXIT("longr1","north");
}

init() {
    ::init();
    add_action("my_listen","listen");
    add_action("my_remove","remove");
}

my_remove(str) {
  if (str == "garland") {
    notify_fail("Oh no! You can't!! Be serious, will you!\n");
    return 0;
  }
}

my_listen(str) {
  if (!str) {
    notify_fail("Listen to what?\n");
    return 0;
  }
  if (str == "to music" || str == "to tones") {
    write("Sitting down, sharpening your ears, make you perceptable to the "+
	  "music. It is a melancolic song which says something about danger "+
	  ", toads, and questions that have to be answered. I think it is "+
	  "some kind of warning or something.\n");
    say(QCTNAME(TP)+" sits down, listening carefully to the music.\n");
    return 1;
  }
}
