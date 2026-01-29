/* Road4 coded by Teth
 * April 4, 1996
 * Last updated oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({"urban", "mixedforest",}) );

object drac1,drac2;

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

        drac2->set_leader(drac1);

        drac1->team_join(drac2);

        drac1->move(TO);
        drac2->move(TO);
    }
}

void
create_darkenwd_room()
{
    set_place(ROAD);

    set_long_desc("This road runs between the village of Solace to the " +
      "southeast and the town of Haven to the northwest. It is the most "+
      "frequently used route, as the Kharolis Mountains stand in the way "+
      "of something more direct. Plants dot the roadside, sometimes "+
      "invading the road. Trees line both sides of this route.");
    AI("plants","Some of these green organisms may be useful.\n");
    add_item("road", "The road is covered with pebbles and stones, nothing " +
             "of terrible interest to one as travelled as you. The "+
             "stones are mostly kicked to the edges of the road, where "+
             "there is little foot or hoof traffic.\n");
    add_item(({"stones","pebbles"}), "They are grey, with the occasional " +
             "one having a mottled black pattern.\n");
    add_item("trees", "The trees that stand here are a mixture of " +
             "both deciduous and evergreen trees. You could probably " +
             "go into the forest.\n");
    AI(({"deciduous trees","evergreen trees"}),"These stand tall and "+
             "watching.\n");

    add_exit(TDIR + "road5", "northwest");
    add_exit(TDIR + "road3", "southeast");
    add_exit(TDIR + "forest3", "northeast",0,4,1);
    add_exit(TDIR + "forest8", "southwest",0,4,1);
   
    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"plants"}), 2);
       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();
   
}




