/* Road2 coded by Teth
 * April 3, 1996
 * Last updated Oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({"mixedforest", "urban", }) );

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
      "southeast and the town of Haven to the northwest. It is known " +
      "that this road runs north of the dreaded Darken Wood. Plants "+
      "line the side of the road here, although they are dwarfed by the "+
      "trees that stand next to them.");
    add_item("plants", "They may contain some useful herbs.\n");
    add_item("road", "The road is covered with pebbles and stones, nothing " +
             "of terrible interest to one as travelled as you.\n");
    add_item(({"stones","pebbles"}), "They are grey, with the occasional " +
             "one having a mottled black pattern.\n");
    add_item("trees", "The trees that stand here are mostly evergreen " +
             "trees. You could probably go into the forest.\n");
    AI(({"evergreen trees","evergreens"}),"These needled trees add a certain "+
        "mystique to the forest.\n");

    add_exit(TDIR + "road3", "northwest");
    add_exit(TDIR + "road1", "southeast");
    add_exit(TDIR + "forest1", "northeast",0,4,1);
    add_exit(TDIR + "forest6", "southwest",0,4,1);
   
    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"plants",}), 2);

       OUTSIDE;  /* An outside room */
   
    reset_darkenwd_room();
}




