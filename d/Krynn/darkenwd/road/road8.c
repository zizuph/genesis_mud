/* Road8 coded by Teth
 * March 5, 1996
 * Last updated Oct 26 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({"mixedforest","urban",}));

object drac1,drac2,drac3;

int
dracs_present()
{
    if (present("baaz",TO) || present("kapak",TO))
        return 1;

    return 0;
}

void
reset_darkenwd_room()
{
    set_searched(random(2));
    if (!dracs_present()) 
    {
        drac1 = clone_object(NPC + "kapak");
        drac2 = clone_object(NPC + "baaz");
        drac3 = clone_object(NPC + "baaz");

        drac2->set_leader(drac1);
        drac3->set_leader(drac1);

        drac1->team_join(drac2);
        drac1->team_join(drac3);

        drac1->move(TO);
        drac2->move(TO);
        drac3->move(TO);
    }
}

void
create_darkenwd_room()
{
    set_place(ROAD);

    set_long_desc("This road runs between the village of Solace to the " +
      "southeast and the town of Haven to the west. It passes " +
      "through the Sentinel Peaks mountain range, a collection of eroded " +
      "hills and older mountains. To the north lies Northfields, some of " +
      "the area's prime agricultural land. The area rises steadily as you " +
      "approach Sentinel Gap, the pass through the mountains. Several " +
      "herbs and shrubs line the road to the south.");
    add_item(({"herbs", "shrubs"}), "They may contain some useful " +
             "herbs, if you search here for them. They also continue " +
             "quite far to the south.\n");
    add_item("road", "The road is covered with pebbles and stones, nothing " +
             "of terrible interest to one as travelled as you.\n");
    add_item(({"stones","pebbles"}), "They are grey, with the occasional " +
             "one having a mottled black pattern.\n");
    add_item(({"Sentinel Peaks", "sentinel peaks", "mountains",
               "mountain range"}), "These mountains are the root of the " +
               "local scenery, causing some beauty and awe.\n");
    add_item("mountain", "One pretty much looks the same as the other, " +
             "each one being some shade of grey and fairly eroded.\n");
    add_item(({"Sentinel Gap", "sentinel gap", "gap", "Gap"}), "It is still " +
             "too far away to distinguish any detail. It would be the ideal " +
             "place for an ambush, however.\n");
    add_item(({"Northfields", "northfields", "agricultural land", "land"}),
             "This area creates much of the local food production, feeding " +
             "many people of all races.\n");
    add_exit(TDIR + "road9", "west",0,2);
    add_exit(TDIR + "road7", "southeast",0,2);
    add_exit(TDIR + "forest11", "south",0,4,1);
   
    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"bushes","herbs",}), 3);
       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();

}




