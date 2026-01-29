/* Road7 coded by Teth
 * March 5, 1996
 * Last updated Oct 26 1996
 */

#include "local.h"
#include <macros.h>

inherit ROADOUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({"urban","mixedforest", }));

#define SEED   KRFOOD + "seed_grain"

int seed_found;

void
reset_darkenwd_room()
{
    set_searched(random(2));
    seed_found = 0;
}

void
create_darkenwd_room()
{
    set_place(ROAD);

    set_long_desc("This road runs east to the village of Solace " +
      "and northwest to the town of Haven. It passes north of the Sentinel " +
      "Peaks mountain range. Nestled in the mountains to the south stands " +
      "a moss-covered tower, keeping a silent vigil. Northfields is a short " +
      "walk to the north. Forest covers the roadside to the west, and " +
      "various plants line the side of the road.");
    add_item("plants", "Some of them appear to be useful.\n");
    add_item("road", "The road here is clear of pebbles and stones, instead "+
             "it is composed of dirt, with several seeds and dried leaves " +
             "embedded within.\n");
    add_item(({"dirt", "soil"}), "The soil is fine and silty, with little " +
             "organic matter, except for the seeds and dried leaves.\n");
    add_item("seed", "One looks pretty much the same as the other.\n");
    add_item("seeds", "The seeds look like they could possibly belong to " +
             "some sort of grass. Perhaps a bag on the back of farmer's " +
             "cart had a leak.\n");
    add_item(({"leaves", "dried leaves"}), "They crumble as you step on " +
             "them with a small crunch.\n");
    add_item(({"Sentinel Peaks", "Peaks", "sentinel peaks", "peaks",
             "mountains", "mountain range"}), "The mountain range " +
             "stretches as far as your eyes can see.\n");
    add_item(({"Northfields", "northfields"}), "The Northfields are covered " +
             "with fields for agricultural use.\n");
    add_item("fields", "They are in non-linear patterns.\n");
    add_item(({"tower", "moss-covered tower", "Gader's Citadel", "Citadel",
             "citadel"}), "The tower is known to the " +
             "local residents as Gader's Citadel. It is covered with a " +
             "blackish-green moss. The granite-grey stone beneath is only " +
             "visible in a few places, but nothing you can see at detail " +
             "from this distance. You can see no path to the Citadel.\n");
    add_item(({"forest","trees"}), "The trees that stand here are a mixture " +
             "of both deciduous and evergreen trees. You could probably " +
             "go into the forest.\n");
    add_exit(TDIR + "road8", "northwest",0,2);
    add_exit(TDIR + "road6", "east",0,2);
    add_exit(TDIR + "forest11", "west",0,4,1);
    add_search(({"dirt","soil"}),1,"find_seed",-20);
 

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"plants","roadside",}), 2);
       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();

}

string
find_seed(object who, string what)
{
    if (seed_found)
    {
    return 0;
    }
 
    say(QCTNAME(who) + " uncovers a seed on the ground!\n");
    clone_object(SEED)->move(TO, 1);
    seed_found = 1;
    return "You expose a seed.\n";
}



