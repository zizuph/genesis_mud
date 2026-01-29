/* Road3 coded by Teth
 * April 3, 1996
 * Updated Oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "mixedforest","urban", }) );

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
      "southeast and the town of Haven to the northwest. The road here " +
      "is well-used with the passage of many travellers. Weeds and such "+
      "blanket the side of the road, while trees tower above them.");
    add_item("weeds", "They may contain some useful herbs.\n");
    add_item("road", "The road is covered with pebbles and stones, nothing " +
             "of terrible interest to one as travelled as you. There "+
             "are several short ruts in the road, presumably from a "+
             "cart.\n");
    AI(({"ruts","short ruts"}),"These ruts appear to be made by the wooden "+
        "wheels of a cart.\n");
    add_item(({"stones","pebbles"}), "They are grey, with the occasional " +
             "one having a mottled black pattern.\n");
    add_item("trees", "The trees tower above the weeds on the side of the " +
             "road, making them look puny in comparison. You could probably " +
             "walk right into the forest.\n");

    add_exit(TDIR + "road4", "northwest");
    add_exit(TDIR + "road2", "southeast");
    add_exit(TDIR + "forest2","northeast",0,4,1);
    add_exit(TDIR + "forest7","southwest",0,4,1);
   
    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"weeds", }), 2);

       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();
   
}




