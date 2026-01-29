/* Road1 coded by Teth
 * April 3, 1996
 * Last updated oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({"urban","mixedforest", }) );

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
      "southeast and the town of Haven to the northwest. It is a "+
      "roundabout route, but necessary due to the Kharolis Mountains which "+
      "get in the way of more direct travel. Herbs and shrubs line the side "+
      "of the road, while trees stand tall over them.");
    add_item(({"herbs", "shrubs"}), "They appear to contain some useful " +
             "plants.\n");
    add_item("road", "The road is covered with pebbles and stones, nothing " +
             "of terrible interest to one as travelled as you. This road "+ 
             "appears well-travelled, by foot, hoof, and cart wheel.\n");
    add_item(({"stones","pebbles"}), "Most of these are stormcloud grey " +
             "with some having an irregular white pattern.\n");
    add_item("trees", "The trees that stand here are a mixture of " +
             "both deciduous and evergreen trees.\n");
    AI(({"deciduous trees","evergreen trees"}),"These trees stand tall, "+
        "watching all that pass in a silent vigil.\n");

    add_exit(TDIR + "road2", "northwest");
    add_exit(SOL_ROAD + "xroad", "southeast");
   
    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"bushes","herbs",}), 3);

       OUTSIDE;  /* An outside room */
    reset_darkenwd_room();

}




