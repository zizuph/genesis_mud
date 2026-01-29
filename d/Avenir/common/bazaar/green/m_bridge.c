// file name: m_bridge.c
// creator(s): Ilyian, April 1995
// last update: Lilith, Oct 2004 -bug fix in check_statue()
// purpose: Center of bridge between park and bazaar islands.
// note:
// bug(s):
// to-do:

inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "../bazaar.h"
#include "/d/Avenir/common/holm/wolf.h"

int check_statue();
int do_climb(string str);

int found;

void
reset_room()
{
    found = 1;
}

void
create_room()
{
    set_short("Apex of arched bridge");
    set_long("You stand at the apex of a steeply arching "+
        "bridge over murky waters. The bridge slopes down "+
        "to the north, ending at the shore of the bazaar "+
        "island, and to the south, where it ends at the "+
        "shore of a thickly vegetated island. The bridge "+
        "is of very solid construction. Below you, the "+
	"dark waters of the sea swirl menacingly, and "+
        "looming above you are a pair of large stone "+
        "statues rising up on either side of the bridge.\n");

    add_exit(BAZAAR+"green/s_bridge","south",0);
    add_exit(BAZAAR+"green/n_bridge","north",0);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_LIGHT,1);
    IN;

    add_item(({"bridge","stone"}), 
        "This bridge is made from a rough grey stone that "+
        "has blackened to a sooty colour over the years. You "+
	"are at the apex of the bridge, high above the swirling sea "+
	"below. The bridge ends at islands both to the north and the "+
	"south, and from this height you can get a good view of both "+
	"of them. Large stone statues rise up here, staring "+
        "stoicly down at you, as if they were guarding something.\n");
    add_item(({"water","sea","ocean"}),
        "The water far below the bridge is completely lightless, "+
        "so you have no indication of either how deep it is, or "+
        "what hides beneath the surface. It gives you an "+
        "uncomortable feeling, and strange eddies swirl in eerie "+ 
        "patterns.\n");
    add_item(({"statue","statues"}),
        "The statues rise high above you on either "+
        "side, one to the left and on to the right.\n");
    add_item(({"island","islands"}),
        "There are two islands, one to the north end of the "+
        "bridge, and one to the south. The northern one seems "+
        "to be a marketplace of sorts, and the on to the south is a "+
        "densly overgrown mass of trees and hedges.\n");
    add_item(({"north island","island","bazaar"}),
        "From your vantage point, you have a good view of the "+
        "bazaar island. It is a crowded mass of buildings, "+
        "vendors, and citizens milling about. The noise of "+
	"haggling reaches your ears even from this distance. "+
        "In the center rises a large hill, upon which a dark "+
        "shape looms. In the southern part of the island is "+
        "a pleasant garden.\n");
    add_item(({"south island","park"}),
        "From this vantage point, you can get a good view of "+
        "the large island to your south. It is covered in "+
	"thick vegetation, and cut up by stone paths, "+
        "bordered on each side by walls. There seems to be a "+
        "large courtyard in the north path of the "+
	"island, and in the center is small hill. "+
        "The south parts of the island are obscured by a "+
        "dense canopy covering it. Large, horse-like "+
	"shapes move around the paths, seemingly grazing.\n");
    add_item(({"left statue","elven statue","west statue",
        "first statue"}),
        "The statue to the west side is of dark black stone "+
        "and depicts an enormous muscular elf, swathed in a "+
        "flowing cloak and holding aloft a thick rod. He "+
        "stares down at you with a glare so realistic that "+
	"you start to feel guilty of crimes you have committed "+
        "in the past.\n");
    add_item(({"right statue","demon statue","demon",
        "east statue","second statue"}), check_statue);

    set_tell_time (110);
	  add_tell ("A warm breeze blows across the bridge, bringing upon "
			 +"it a strange scent.\n");
	  add_tell ("The sea below you swirls and churns in strange eddies.\n");
	  add_tell ("From the north island, you hear the distant call of "
			 +"hawkers selling their wares.\n");
          add_tell ("A bit of driftwood floats by beneath the bridge\n");


    reset_room();

}

void
enter_inv(object ob, object from)
{
	start_room_tells();
	::enter_inv(ob, from);
}


void
init()
{
    ::init();

    add_action(do_climb, "climb");
}

string
check_statue()
{
    string str;

    str = "The statue to the east side of the bridge is of a titanic "+
          "demon, holding a thick, spiked whip. Its wings are spread "+
          "far apart, and it looms dangerously over you, almost as if "+
          "it would leap down upon you at any moment.";

    if (found)
        str +=" A skull bone is sitting on its head.";
    
    return str +"\n";
}

int
do_climb(string str)
{
    object bone;
    
    notify_fail("Climb what?\n");
    if(!str)
    return 0;

    if (str == "statue")
    {
 	write("Climb which statue?\n");
	return 1;
    }

    if (str == "left statue")
    {
	write("You don't want to.\n");
	return 1;
    }

    if (str == "right statue")
    {
/*       	if (this_player()->query_skill(SS_CLIMB) < 3)
	{
            say(QCTNAME(this_player()) + " tries to climb the "+
               "right statue but fails.\n");
            write("You try to climb up the statue, but are "+
                "too unskilled to succeed.\n");
            return 1;
	}
*/
        if (found < 1)
	{
	    say(QCTNAME(this_player())+ " climbs the right "+
                "statue and looks around, then quickly returns.\n");
            write("You climb the right statue. At this height "+
                "you have an excellent view of the bazaar and "+
                "part of the island. After a quick look, you "+
                "climb back down.\n");
	    return 1;
        }

	//If there are any bones here, the following will process.
	found--;
	bone = clone_object(WOLF_BONE + "skull.c");
	bone->move(this_player(), 1);

        say(QCTNAME(this_player())+ " climbs the right "+
            "statue and looks around, then quickly returns.\n");

	write("You climb up the statue and get a skull bone, "+
	    "then climb back down.\n");
	return 1;
    }

    else
    {
	return 0;
    }

}
