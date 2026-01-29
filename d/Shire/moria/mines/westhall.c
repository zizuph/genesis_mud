#include "defs.h"

CONSTRUCT_ROOM
{
    set_short("West end of a brightly lit hall");
    set_long(
	"You are in the western end of a brightly lit hall. The hall is "+
	"domed and big chandeliers illuminate the whole room. There is an "+
	"exit in the west here.\n");
    add_item("ceiling",
	"The ceiling is domed and big chandeliers illuminates the room from "+
	"above. You would reckon the ceiling to be about 20 meters (60 feet) "+
	" above you, and you could not possibly reach the chandeliers.");
    add_item("walls",
	"This room has been decorated in the famous 'leaves&trees' pattern "+
	"often found in the late ages of the dwarves in Khazad-dum. Interleaving "+
	"trees and leaves adorns the walls from the floor to the top in "+
	"several colours. It almost seems like you are in the middle of a large "+
	"forest, yet another proof of the magnificient architecture skills of the "+
	"Naugrim before they were forced out of these mines by the trolls.");
    add_item(({"leaves","trees", "pattern"}),
	"This pattern is highly irregular, and you can't even figure out "+
	"when the pattern repeats itself. It almost looks like you are in "+
	"mid forest, a remarkable impression indeed.");
    add_item("floor",
	"The floor is not flat at all. It is highly irregular, as if you were "+
	"walking outdoor! In fact, there are green spots and stones around and "+
	"even what seems to be mud!");
    add_item(({"spots","green spots"}),
	"It looks almost like grass, but when you examine it, you see that it "+
	"is just an illusion. It is just green rocks which looks like grass.");
    add_item("stones",
	"The stones seems melted into the wall somehow. Hmm, it seems like "+
	"the dwarves really put an effort to create this room as close to "+
	"outdoor rooms as possible.");
    add_item("mud",
	"Stepping on it, you realize that it is in fact not mud at all. It is "+
	"just the colour which makes it seem to look like it. Strange.");
    add_item(({"lights", "chandeliers"}),
        "The chandeliers shine remarkably brightly and illuminate the whole "+
	"hall. They are fastened up in the ceiling and you could not possibly "+
	"reach up there.");

    add_prop(ROOM_I_LIGHT, 10);

    WEST("narrpass");
    EAST("easthall");
}
