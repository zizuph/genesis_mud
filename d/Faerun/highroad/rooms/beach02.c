/*
 * Beach south of the High Road, Avenir Pier, beach02
 * -- Finwe, July 2006
 * Utilized for Pan-Donut Circle line, Tapakah, 05/2009
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "/d/Faerun/ships/defs.h"
#include "/d/Faerun/sys/mudtime.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;
inherit "/d/Genesis/gsl_ships/lib/pier";
//void add_stuff();
void set_add_beach();

string extra_line = "";
object ship;

#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
static object  sign;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("A secluded beach");
    set_extraline("The beach is rocky and secluded. Sparse grass grows on the beach between the rocks and sand. Debris has been washed up on it from the constant waves that crash on the beach. Ruts are visible where many boats landed here from Avenir, but come no more. Crabs scuttle away from you and hide.");

    reset_room();
    add_room_tell("Seagulls squawk overhead.");
    add_room_tell("Some waves lap at the beach.");
    add_room_tell("A crab scuttles across the beach.");
    add_room_tell("A large wave crashes on the beach, spraying water " +
        "into the air.");
    add_room_tell("Some birds race across the sand.");
    
//    add_stuff();
    set_add_beach();

    add_exit(HR_DIR + "str02", "northeast");
    add_exit(HR_DIR + "beach01", "west");
}

public void
init()
{
    ::init();

}
void
reset_room()
{

}

/*
 * Function name : set_add_beach
 * Description   : adds descr of beach
 */
void set_add_beach()
{
    add_item(({"rough trail", "trail", "path"}),
        "The trail wanders up the beach and over the shoreline then " +
        "disappears. It looks well used.\n");
    add_item(({"shoreline", "coastline"}),
        "It is a rocky line that marks the end of the coast. The shoreline " +
        "overhangs the beach slightly with grasses growing along it.\n");
    add_item(({"grasses"}),
        "The grasses are gray and thin looking. They grow in patches " +
        "in the sand near the shoreline.\n");
    add_item(({"beach"}),
        "Miles of sand and gravel stretch from the shoreline to the sea. " +
        "Waves lap at the shoreline while seagulls and other waterfowl " +
        "squabble over scraps of food. Seashells and driftwood are " +
        "scattered liberally across the sand forcing you to weave in " +
        "and out to sidestep tripping over them. Further down the beach, " +
        "you notice jetsam strewn about where the tide deposited it as " +
        "it washed ashore.\n");
    add_item(({"sand"}),
        "The sand is grey and coarse looking with gravel mixed in with it. " +
        "Sand crabs skitter across the sugary surface chasing sand " +
        "fleas and other insects.\n");
    add_item(({"jetsam"}),
        "Washed onto the shore, jetsam litters the beach amongst the " +
        "driftwood and seashells. It is useless trash, made up of mostly " +
        "from the remnants of former ships and cargo.\n");
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
        "yellow legs. The birds live along the sea and are often found " +
        "fighting over bits of food on the beach or soaring around the " +
        "water.\n");
    add_item(({"gravel", "rocks"}),
        "They are gray colored and mixed in with the sand making the " +
        "beach rough. The gravel is all sizes ranging from small pebbles " +
        "to rocks the size of a fist. Most of the rocks are smooth from " +
        "being tossed around in the water.\n");
    add_exit(HR_DIR + "str01", "north");

  sign = clone_object(SIGN);
  sign->move(TO);
  add_pier_entry(MASTER_OB(TO), "Faerun", "Pan-Donut Circle");
  initialize_pier();

}


object
query_sign ()
{
  return sign;
}

