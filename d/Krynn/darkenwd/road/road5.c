/* Road5 coded by Teth
 * April 3, 1996
 * Last update Oct 26, 1996
 */

#include "local.h"

inherit ROADOUT;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({ "urban","mixedforest",}));

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
      "southeast and the town of Haven to the northwest. This route is "+ 
      "the shortest distance between the town and village. Herbs and shrubs "+
      "line the roadside, while it appears that you can enter the forest "+
      "by going northeast or southwest.");
    add_item(({"herbs", "shrubs"}), "They appear to contain some useful " +
             "herbs.\n");
    add_item("road", "The road looks well-travelled by foot, hoof and " +
             "cart wheel.\n");
    add_item(({"forest","trees"}), "The trees that stand here are a mixture "+
             "of both deciduous and evergreen trees. You could probably " +
             "go into the forest.\n");
    AI(({"deciduous trees","evergreen trees"}),"They are a component of this "+
        "healthy-looking forest.\n");

    add_exit(TDIR + "road6", "northwest");
    add_exit(TDIR + "road4", "southeast");
    add_exit(TDIR + "forest4", "northeast",0,4,1);
    add_exit(TDIR + "forest9", "southwest",0,4,1);
   
    seteuid(getuid(TO));
    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({"bushes","herbs", }), 3);

       OUTSIDE;  /* An outside room */

    reset_darkenwd_room();
   
}




