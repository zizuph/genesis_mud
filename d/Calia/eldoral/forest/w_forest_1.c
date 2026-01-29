#pragma strict_types

#include "defs.h"

inherit FORESTBASE;

public void
create_room()
{
    extra = "Progress to the north is impeded by a steep ravine that " +
        "cuts through the stone, extending from the shoreline all " +
        "the way to the crumbling wall marking the ruins of a " +
        "castle to the east. ";
    extra += "To the east, the crumbling remains " +
        "of a small structure stand. Whatever its purpose was while it " +
        "stood, it serves now only as an obstacle, and a place for moss " +
        "and small plants to find root. ";

    add_item(({"remains", "structure", "small structure"}),
        "These ruins may have once been someone's home, but now are " +
        "home only to a myriad of insects and plant life.\n");
    add_item(({"castle", "ruins"}),
        "The wall, though crumbling, blocks your view of the " +
        "castle ruins for the most part. Only a few of the " +
        "highest towers rising above the wall give it away " +
        "as a castle.\n");
    add_item(({"towers"}),
        "Tall and jagged, the towers of the castle ruins are " +
        "on the verge of collapse. The grey stone from which " +
        "they are made must be very old indeed, as its crumbling " +
        "away in large pieces.\n");
    add_item(({"wall", "massive wall", "crumbling wall"}),
        "To the east, a massive wall rises between you and the " +
        "ruins of a castle. How much longer it will stand is " +
        "another thing, as it appears to be on the verge of " +
        "collapse. Most of it's top has already crumbled away " +
        "to dust, and the decay is slowly spreading down " +
        "the surface of the wall.\n");
    add_item(({"ravine", "steep ravine"}),
        "The ground here suddenly drops steeply down the stoney " +
        "cliff face of a ravine to the north, as if a scythe of " +
        "godlike proportions had sliced away the very stone " +
        "of the island here.\n");
    add_prop(DAGGER_AS_SEARCH_TARGETS, ({"structure", "ruins", 
        "rubble"}));

    create_cliff();
    create_forest();
    add_exit(FOREST + "w_forest_3", "south");
}
