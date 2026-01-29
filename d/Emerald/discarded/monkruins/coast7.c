/*
 * COAST7.c
 * Coastal Road leading to the ruins of Kamesh.
 * - Alaron December 1996
 */

#include "/d/Emerald/defs.h"
#include "default.h"
#include <ss_types.h>

inherit "/std/room";

void
create_room()
{
    set_short("Dark, foggy path");
    set_long("   You are standing in the middle of a heavy overcast of "+
	     "mist and fog. The fog is so heavy that simply by standing "+
	     "here it is depositing water droplets on your clothing. The "+
	     "small, coastal path here is old and overgrown. The only "+
	     "indication that it was once a busy travel lane are the "+
	     "ancient ruts worn into the soil by the wagon traffic "+
	     "ages ago. A few dark shadows of trees can be seen around "+
	     "the road. Enormous, towering shadows of ancient, broken "+
	     "buildings lurk in the shadows beyond the mist to the "+
	     "south. In the middle of the road is a huge iron gate "+
	     "which has been bent over and broken. The road continues "+
	     "to the north and south beyond the gate.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"overcast", "mist", "fog", "droplets", "water droplets"}),
	     "The heavy fog here looms over the entire area like a dark "+
	     "shadow, dampening and distorting the view of the surroundings. "+
	     "Peering through the fog, you notice several shadows of "+
	     "ancient, broken buildings and a few trees.\n");

    add_item( ({"path", "ground", "ruts", "ancient ruts", "rut", "tracks"}),
	     "The path here is overgrown and not much more than flattened "+
	     "grass and weeds. The only indication that it was once anything "+
	     "more than this is the appearance of deep, ancient ruts in "+
	     "the ground indicative of the wagon traffic that at one time "+
	     "must have been quite heavy.\n");

    add_item("shadows",
	     "There are hundreds of shadows and dark shapes lurking off in "+
	     "the distance. Which shadows are you trying to examine? Those "+
	     "of the trees? The buildings?\n");

    add_item( ({"buildings", "building", "building shadows", "ruins",
		"broken buildings", "ancient buildings"}),
	     "As you peer through the dark veil of fog covering the road "+
	     "you notice immense structures just to the south. The buildings "+
	     "are broken and have jagged outlines, as if entire pieces of "+
	     "the buildings are missing. They look as if they are ruins "+
	     "of some kind. From this distance, you can't quite tell "+
	     "what type of place this used to be.\n");

    add_item( ({"trees", "tree", "tree shadows", "shadows of trees"}),
	     "The trees are barely visible here. The fog here reduces the "+
	     "images of the trees to nothing more than a dark, columnar "+
	     "shadow with a tree-like top. In fact, had you not seen those "+
	     "trees closer before, you might not know what they were.\n");

    add_item( ({"gate", "iron gate", "huge iron gate", "huge iron gate",
		"broken gate", "broken iron gate"}),
	     "The huge, iron gate in the middle of the road is broken "+
	     "and bent. It was originally a fancy design of tall iron "+
	     "rods fenced together with three horizontal iron beams, all "+
	     "scrolled and decorated with a classic 'arrowhead' motif. At "+
	     "either side of the road is an enormous stone block which held "+
	     "the incredibly large hinges for the gate. The hinges are long "+
	     "since destroyed, as is the fence which continued away from the "+
	     "road on the far side of each block. Occasionally you can "+
	     "see the odd piece of iron resting in the bushes as a subtle "+
	     "reminder to the history of the fence.\n   There is a large, "+
	     "tarnished silver plate hanging by a rusted chain in the middle "+
	     "of the gate.\n");

    add_item( ({"fence", "broken fence", "missing fence"}),
	     "There is little remaining of the fence which used to "+
	     "surround the property to the south. All that remains now are "+
	     "a few rusted piece of iron and some old stone blocks.\n");

    add_item( ({"plate", "silver plate", "tarnished silver plate",
		"large plate", "large silver plate"}),
	     "The plate is obviously very old. The fact that silver was "+
	     "used in the construction of a simple informative sign "+
	     "is suggestive of its age alone, and perhaps the wealth of "+
	     "the owners of this eerie place. There is some barely-visible "+
	     "writing scribed into it beneath the ages of tarnish.\n");

    add_cmd_item(({"writing", "plate", "silver plate"}),
		 "read",
		 "The plate contains writing in an incredibly old "+
		 "style of script. After a few seconds of careful "+
		 "examination you manage to read:\n"+
		 "                Monastery Kamesh\n"+
		 "                  NO ADMITTANCE\n");

    add_exit(MONKRUIN_DIR + "coast8", "south", "@@dis_check@@", 4);
    add_exit(MONKRUIN_DIR + "coast6", "north", 0, 2);
}

/*
 * This function checks the player's self discipline. No one
 * with a DIS of less than 30 can even venture into the ruins.
 * This isn't a very harsh requirement, but the theme-explanation
 * is fear. People < 30 DIS are simply too scared to venture into the
 * ruins.
 */
int
dis_check()
{
    int dis;

    dis = this_player()->query_base_stat(SS_DIS);

    if (dis < 30)
    {
	write("You attempt to step through the gate, but as soon as you "+
	      "get halfway through, you are suddenly overcome with a "+
	      "terrible fear! You feel as though something is incredibly "+
	      "wrong here! You back away in terror!\n");
	say(QCTNAME(TP) + " attempts to step through the gate, but as "+
	    "soon as "+TP->query_pronoun()+ " gets halfway through, "+
	    TP->query_pronoun()+" recoils in absolute fear!!\n");
	return 1;
    }
    else
    {
	write("You pass through an opening in the broken gate. As you "+
	      "step through you feel an unsettling chill run through "+
	      "your spine ...\n\n");
	return 0;
    }
}
