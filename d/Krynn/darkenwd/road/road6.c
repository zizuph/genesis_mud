/* Road6 coded by Teth
 * March 19, 1996
 * Last updated oct 26 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "urban","mixedforest", }));

void
reset_darkenwd_room()
{
    set_searched(random(2));
}

void
create_darkenwd_room()
{
    set_place(ROAD);

    set_long_desc("This road runs between the village of Solace to the " +
      "southeast and the town of Haven to the west. It passes " +
      "through the Sentinel Peaks mountain range, an old set of mountains. " +
      "Far to the west you can make out the entrance to Sentinel Gap, a "+
      "mountain pass. Various herbs, shrubs, and trees line the road to the " +
      "northeast and southwest.");
    add_item(({"herbs", "shrubs"}), "They appear to contain some useful " +
             "herbs. Perhaps you should search here for them?\n");
    add_item("road","The road is covered with pebbles and stones, nothing " +
             "of terrible interest.\n");
    add_item(({"Sentinel Peaks", "sentinel peaks", "mountains",
               "mountain range"}), "These mountains are a credit to the " +
               "local scenery.\n");
    add_item("mountain", "One pretty much looks the same as the other, " +
             "each one being some shade of grey and fairly eroded.\n");
    add_item(({"Sentinel Gap", "sentinel gap", "gap", "Gap", "mountain pass",
             "pass"}), "It is too far away to distinguish anything. It " +
             "would be the ideal place for an ambush, however.\n");
    add_item(({"stones","pebbles"}), "They are black, with the occasional " +
             "one having a mottled grey pattern.\n");
    add_item(({"trees", "forest"}), "The trees that stand here are a " +
             "mixture of both deciduous and evergreen trees. You could " +
             "probably go into the forest.\n");
    add_item("deciduous trees", "They are easily identifiable as birch and " +
             "poplar trees.\n");
    add_item(({"birch", "birch trees", "poplar", "poplar trees"}), "Very " +
             "beautiful deciduous trees indeed.\n");
    add_item("evergreen trees", "They are mostly Crystalmir pine.\n");
    add_item(({"Crystalmir pine", "crystalmir pine", "pine", "pine trees"}),
             "Straight growing, these Crystalmir pines look to have been " +
             "untouched for many years.\n");
    add_exit(TDIR + "road7", "west",0,2);
    add_exit(TDIR + "road5", "southeast");
    add_exit(TDIR + "forest5", "northeast",0,4,1);
    add_exit(TDIR + "forest10", "southwest",0,4,1);
   
    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"bushes","herbs",}), 2);
       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();

}




