/*
 * Beach south of the High Road, Shire Pier, beach04
 * -- Finwe, July 2006
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
void add_stuff();
void set_add_beach();

string extra_line = "";
object ship;

void
create_road()
{
    add_prop(ROOM_S_MAP_FILE,"highroad_map.txt");
    set_short("A rocky cove");
    set_extraline("The shoreline dips suddenly into the water, disappearing from view. The cove is hidden from view and probably a common place for smugglers and ships who sail from the Shire to land. Some birds fly overhead, skimming the water or flying out to sea. A rough trail leads southeast.");

    reset_room();
    add_room_tell("Seagulls squawk overhead.");
    add_room_tell("Some waves lap at the beach.");
    add_room_tell("A crab scuttles across the sand.");
    add_room_tell("A large wave crashes on the beach, spraying water " +
        "into the air.");
    add_room_tell("Some birds races across the sand.");
    
    add_stuff();
    set_add_beach();

    add_exit(HR_DIR + "beach03", "southeast");
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

public void
add_stuff()
{
	seteuid(getuid(this_object()));
	if (!ship)
	{
		ship = clone_object("/d/Faerun/ships/shire/ship");
		ship->start_ship();
	}
}

public void
restart_ship(string reason)
{
	if (!reason)
	{
		write("You need a reason to restart a ship!\n");
		return 0;
	}
	
    (ship->query_captain())->remove_object();
	ship->remove_object();
	add_stuff();
	write_file("/d/Faerun/log/shiprestart", extract(ctime(time()), 4, 15)
        + " Faerun to Sparkle " + capitalize(this_player()->query_real_name())
        + " " + reason + "\n");
        write("Ship restarted.\n");
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
	    "Commonly found on beaches, these tiny crabs spend most of " +
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
    add_item(({"gravel", "rocks"}),
        "They are gray colored and mixed in with the sand making the " +
        "beach rough. The grave is all sizes ranging from small pebbles " +
        "to rocks the size of a fist. Most of the rocks are smooth from " +
        "being tossed around in the water.\n");
}
