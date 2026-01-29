/*
 * F58
 * Forest of Coramar
 * 2nd base of the plateau, this one is the important one.
 * See quest documentation for entrance quests to Druids.
 * Alaron March 1998
 */


#include "dirheader.h"
#include "coramar.h"

inherit BASEFOREST;

void
init()
{
  ::init();
  add_action("climb_cliff", "climb");
}

void
create_forest()
{
    set_short("A clearing at the base of a cliff");

    set_long("   The normally thick layer of mist seems to thin out here. The fog still "+
	     "surrounds the path on three sides, distorting the outline of the massive "+
             "trees of the forest behind a thick gray shroud. The clearing here is "+
             "not very large, but is still a welcome sight after the dull, mind-numbing "+
	     "grayness of the rest of the forest. The south and southeast edges of "+
             "the clearing are bordered by a tremendous cliff face. The face is "+
	     "completely "+
	     "flat, and unnaturally smooth. A thin trickle of daylight filters into "+
	     "the small clearing, illuminating a very small section of the cliff "+
	     "face.\n\n");

    add_item( ({"cliff", "cliff face", "face", "granite"}),
	     "The face of the cliff is extremely impressive. The rock is very flat, "+
	     "and seems unnaturally smooth. You "+
             "have never known a rock formation this large to be so smooth. You peer to "+
	     "the southeast and to the southwest, attempting to find the edge of the "+
	     "cliff, but the edges curve as if the cliff was a giant cylinder and "+
	     "disappear behind the mist.\n");

    remove_item("up");

    add_item( ({"up", "above", "sky", "light", "sunlight", "day", "daylight"}),
	     "You step close to the cliff face, feeling the warmth of the filtered "+
             "daylight hit your face. Craning your neck back as far as it will go, you "+
	     "look up along the cliff face. The faint traces of the mist floating above "+
	     "you make it seem as though you are peering through a thin, white fabric. "+
	     "Squinting painfully up into the daylight, you notice a dark gray shape at "+
	     "very top of the cliff.\n");

    add_item( ({"shape", "dark shape", "gray shape", "dark gray shape", "grey shape",
	     "dark grey shape"}),
	     "You rub your eyes and then squint up through the sunlight near the "+
	     "cliff face. Your eyes instantly focus on the dark shape this time. Your "+
             "hunch that the cliff is actually an enormous plateau jutting out of the "+
             "forest. At this height you wonder why you didn't see it when you first "+
	     "entered the forest. As you study the tiny piece of the shape that is "+
	     "visible atop the plateau, comprehension dawns on you. The shape resting "+
	     "on the plateau is that of a parapet! There is a castle atop the plateau!\n");

    add_item( ({"castle", "parapet"}),
	     "You squint and crane your neck further back, but from the bottom of the "+
	     "cliff face, you can see nothing more than the very tip of a parapet far "+
	     "above.\n");



    add_fexit(CORAMAR+"f57", "southeast", 0);

}

int
climb_cliff(string str)
{
    if ( (str == "cliff") || (str == "plateau") ) {
        write("You could try, but the cliff is far to smooth, and has no natural "+
              "formations on it for foot and hand holds.\n");
	return 1;
    }
    else {
	notify_fail("Climb what?\n");
        return 0;
}
}
