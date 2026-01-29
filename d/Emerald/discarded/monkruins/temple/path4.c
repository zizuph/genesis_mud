/*
 * PATH4.c
 * This is the path just outside the Temple of the Doomed.
 * Originally by Starninja, re-done for hooks into new MonkRuins.
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "../default.h"

inherit "/std/room";

void create_room()
{
    object door;
 
    set_short("Mist-shrouded path outside the ruins of a monastery");
    set_long("   You are on a well-trod path which runs an east-west "+
	     "course. You try to discern the end of the path but the "+
	     "mist prevents you from seeing any more than a few meters. To "+
	     "the east is an enormous, black-marble building. Through the "+
	     "mist elsewhere it was fairly indistinguishable. However, "+
	     "from this close up you can tell that it is a temple of some "+
	     "kind. It is a large, rectangular building with a flat "+
	     "stone-slab roof. In the middle of the stone slab there is a "+
	     "gleaming silver pyramid which rises up out of the temple. The "+
	     "front of the temple seems to glow as the golden entrance "+
	     "almost appears to radiate light.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"temple", "marble temple", "black marble", "marble"}),
	     "It looks like a fairly quiet place. This temple could "+
	     "have been where the monks from the ruined monastery "+
	     "worshipped. Something about this temple troubles you, but "+
	     "you can't quite figure out what. Despite the quiet "+
	     "surroundings, you think you hear the faint sound of "+
	     "something that resembles chanting. It seems to be coming "+
	     "from the direction of the temple.\n"+
	     "There are thick columns in a recessed portion of the "+
	     "front of the building. Behind the columns are narrow "+
	     "windows in the stone.\n");

    add_item( ({"columns", "thick columns"}),
	     "As you approach the columns, you notice that they have "+
	     "been decorated. Carvings of elven and human figures "+
	     "in odd ritual scenes adorn the face of the columns all the "+
	     "way from the base to the top.\n");

    add_item( ({"windows", "narrow windows"}),
	     "Carefully approaching the windows, you peer through one "+
	     "of the narrow windows and see the inner rooms of the "+
	     "temple. Within the temple you notice movement of shadows. You "+
	     "cannot be sure about what you saw since the windows are "+
	     "narrow ... It could have been a trick of the lighting.\n");

    add_exit(MONKRUIN_DIR + "mr2", "north", 0);
 
    door=clone_object(TEMPLE_DIR + "doors/door1_a");
    door->move(this_object());
}
