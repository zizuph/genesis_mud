/*
 * Base file for beach and pier rooms in Faerie
 * By Finwe, April 2005
 */

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit S_LIB_CLOCK;
inherit COMMON_BASE;

void create_beach_room() {}
void set_add_sea();

int room_num;

string extra_line = "";
public void
create_room()
{

    reset_room();
    set_short("A windswept beach");
//    set_long(short() + ". " + s_desc_sky_outside_sky() + " " + extra_line);

    create_beach_room();
    set_add_sea();
    reset_faerie_room();
    s_item_sky_outside();

    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

}

/*
 * Function name : set_add_sea
 * Description   : adds descr of sea
 */
void set_add_sea()
{
    add_item(({"sea", "ocean", "lake"}),
        "This mysterious, dark body of water is the sea that encompasses " +
        "the northern coastal regions of Faerie. The waters look restless " +
        "and choppy, but many boats, ships, and other sea-going vessels " +
        "endure the hardships of sailing upon it. In the distance, you " +
    	"see flotsam undulating in the restless waves occassionally being " +
	    "pelted against the hulls of passing ships and boats.\n");
    add_item(({"water", "waters"}),
        "The water is clear but dark and choppy. The deep blue color " +
        "suggests great depths, hiding great mysteries beneath the " +
        "white-capped waves.\n");
    add_item(({"ship", "ships", "boat", "boats", "vessel", "vessels"}),
        "You see various boats and ships making their way through the " +
        "choppy waves of the deep blue sea. Each vessel takes a turn " +
        "disappearing from view as it bobs up and down the rolling, " +
        "unsettled surface. Strange flags and writing on some of the " +
	    "ships indicate they are arriving from foreign lands of great " +
	    "distance. Others are sailing away to destinations unknown, and " +
        "still more are engaged in earning a living by fishing and diving " +
    	"into the darkened depths.\n");
    add_item(({"waves", "white-capped waves"}),
    	"The waves are capped with with white foam stirred up by the wind " +
	    "and other forces of nature hard at work upon the surface of the " +
    	"water. Seemingly rough and uninviting at first, the waves " +
	    "send fountains of seaspray high into the air.\n");
    add_item(({"foam", "white foam"}),
        "It is a mixture of small bubbles stirred up by the wind and " +
        "sea. It tops most of the waves on the lake.\n");
    add_item(({"bubbles", "small bubbles"}),
        "They are too small to see from here.\n");
    add_item(({"seaspray", "fountains"}),
    	"They are tiny water droplets that fly up fom the lake. It " +
        "the spray is mesmerizing, and relaxing.\n");
    add_item(({"flotsam"}),
        "This flotsam is from shipwrecks and cargo lost overboard by " +
        "ships out at sea. Although the debris looks interesting, the " +
    	"shattered bits and pieces are completely useless after being " +
	    "pounded by the relentless waves.\n");
}

/*
 * Function name : set_add_beach
 * Description   : adds descr of beach
 */
void set_add_beach()
{
    add_item(({"beach"}),
        "Miles of white sand stretch down the coastline where the land " +
	    "reaches out to meet the sea. Frosted, foamy waves lap hungrily " +
	    "at the shoreline while seagulls and other waterfowl squabble " +
	    "over scraps of food. Seashells and driftwood are scattered " +
        "liberally across the sand forcing you to weave in and out to " +
	    "sidestep tripping over them. Further down the beach, you notice " +
	    "jetsam strewn about where the tide deposited it as it washed " +
	    "ashore.\n");
    add_item(({"sand"}),
        "The sand is very fine and white and has the consistency and look " +
	    "of sugar. With each step, your feet sink deeply into the sand " +
	    "making added exertion necessary to walk across it. Upon closer " +
        "inspection, you notice that the sand is teeming with life. " +
	    "Unusual, white sand crabs skitter across the sugary surface " +
	    "chasing sand fleas and other insects.\n");
    add_item(({"jetsam"}),
        "Washed onto the shore, jetsam litters the beach amongst the " +
        "driftwood and seashells. Now useless trash, you can identify " +
        "some of the flotsam as remnants of former ships and cargo.\n");
    add_item(({"driftwood"}),
        "These are pieces of wood that have been out to sea and are " +
        "now washed up on the beach. They are all shapes and sizes, " +
        "and are smooth from floating around in the water.\n");
    add_item(({"shells", "seashells"}),
        "They are the remains of clams, oysters, and other animals from " +
        "the sea. They are scattered across the sand.\n");
    add_item(({"clamshells", "clam shells"}),
        "These are the remains of clams from the sea. They are thick, " +
        "white, and ribbed. Many are broken and scattered across the " +
        "beach or partially buried in the sand.\n");
    add_item(({"oystershells", "oyster shells"}),
        "These are smooth shells that were once oysters. They are broken " +
        "and washed up on the beach. Some are buried in the sand, and " +
        "others scattered across the beach.\n");
    add_item(({"sand crab", "crab", "sand crabs", "crabs"}),
	    "Commonly found on beaches, these tiny crabs spend most of the " +
	    "time scurrying back and forth trying to get enough to eat.\n");
    add_item(({"sand fleas", "fleas"}),
        "Small and annoying, these fleas inhabit the beach. They hop " +
        "around and avoid being caught by the sand crabs that chase " +
        "them.\n");
    add_item(({"gulls", "seagulls"}),
        "They are mostly white birds with long, pointed wings and short " +
        "yellow legs. The birds live along the lake and are often found " +
        "fighting over bits of food on the beach or soaring around the  " +
        "water.\n");
}

/*
 * Function name : set_add_forest
 * Description   : adds descr of forest as seen from beach
 */
void set_add_forest()
{
    add_item(({"evergreen trees", "conifer trees", "evergreen",
            "evergreens", "conifers", "conifer", "tall evergreen tree",
            "tall evergreen trees", "tall trees"}),
        "Tall firs fill the forest. They fill the sky and block out " +
        "much of the light. \n");
    add_item(({"fir trees", "firs", "evergreen trees", "tall fir trees",
            "tall fir tree"}),
        "These evergreens make up the forest. Their thick " +
        "branches spread out, forming a canopy above you.\n");
    add_item(({"canopy"}),
        "It is made up of tops of tall trees that block your view of " +
        "the sky. It is irregularly shaped, but still allows some light " +
        "to filter into the forest.\n");
    add_item(({"forest"}),
        "The forest is large and stretches in all directions. " +
        "Tall trees grow everywhere. Some have fallen over and block " +
        "paths in the forest while others grow tall and block the " +
        "sky above. Fallen branches, pine needles, and other " +
        "debris cover the forest's floor. Light slants through the " +
        "trees.\n");
    add_item(({"conifer", "conifer trees", "conifers", "evergreen",
            "evergreen tree", "evergreen trees", "evergreens", "fir",
            "fir tree", "fir trees", "firs", "tall evergreen tree",
            "tall evergreen trees", "tall fir tree", "tall fir trees",
            "tall trees", "trees"}),
        "The trees form a thick, green border along the southern ridge " +
        "above the beach. The trees look majestic and old, and rise " +
        "into the sky.\n");
    add_item(({"ridge"}),
        "It is a long, narrow strip of land situated above the beach. " +
        "It looks rocky and is lined with trees.\n");

}


/*
 * Function name : set_add_valley
 * Description   : adds descr of valley between Sparkle and Faerie
 */
void set_add_oak_trees()
{
    add_item(({"oak trees", "oak tree", "oaks"}),
        "These are tall, ancient trees. Their large branches reach " +
        "outward and up to the sky and are covered with a multitude " +
        "of emerald green leaves. They grow in groups scattered among " +
        "the fir trees.\n");
    add_item(({"oak leaves", "oak leaf"}),
        "The leaves are long and emerald green. On both sides of the " +
        "leaves are three or four large rounded edges. The top of the " +
        "leaves have a large round edge.\n");
    add_item(({"oak branches"}),
        "They reach outward and up to the sky. They are large and " +
        "covered with many emerald green leaves.\n");
    add_item(({"oak trunk", "oak trunks"}),
        "The tree trunks are tall and and very large. Branches at the " +
        "top reach outward and are covered with many leaves.\n");
}

/*
 * Function name : set_pier_top
 * Description   : adds descr of the pier above the beach
 */
void set_pier_top()
{
    add_item(({"pier", "dock", "quay", "wharf"}),
        "This is a platform that extends out into the water from the " +
        "shore and allows vessels from faraway lands to anchor here. The " +
        "pier is wide and covered with wood slats. Large logs are sunk " +
        "into the beach and support the pier. Metal cleats are spaced " +
        "evenly along the edge of the pier.\n");
    add_item(({"piles", "pilings", "piling"}),
        "These are large logs driven into the water and shore, and support " +
        "the pier.\n");
    add_item(({"logs", "large logs"}),
        "These are cut from the forest and used as pilings for the pier.\n");
    add_item(({"cleats", "metal cleats"}),
        "They are raised horizontal bars attached to the pier. They are " +
        "spaced evenly along the pier's edge and allow ships to be tied up " +
        "and not float away.\n");   
}

/*
 * Function name : set_pier_bottom
 * Description   : adds descr of the pier from beneath it
 */
void set_pier_bottom()
{
    add_item(({"pier", "dock", "quay", "wharf", "platform"}),
        "It extends out into the water from the shore. The platform is " +
        "wide and made of wood, and supported by evenly spaced pilings " +
        "along the edge of the pier.\n");
    add_item(({"pilings", "piles"}),
        "These are large logs driven into the sand and the water, and " +
        "support the platform. The pilings in the water are ringed with " +
        "barnacles.\n");
    add_item(({"barnacles"}),
        "They are sea creatures that grow in a white shell. The pilings " +
        "in the water are covered with them just barely under the water.\n");    
}
