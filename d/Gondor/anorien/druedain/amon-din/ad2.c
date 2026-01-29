/*
 *  This is ad2.c
 *
 *  June 1995 by Gorboth
 */

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <language.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/common/lib/clock.h"

void
create_room()
{
  set_short("In a small clearing at the base of Amon Din");
  set_long(BSN(
    "The trees and vegetation have fallen away here to allow for a small " +
    "clearing. You stand at the base of Amon Din, which rises before you " +
    "directly to the north. A small path makes its way up the hill to the " +
    "northwest where the trees once again resume growth."));
    add_item(({"hill","amon din"}), "@@exa_hill");
    add_item(({"path"}), BSN(
      "The path winds its way up the slope and disappears amongst the trees " +
      "to the northwest."));
    add_item(({"peak","building","top"}), BSN(
      "Still far below the peak of Amon Din, you are able to see little " +
      "detail of its contents. It is clear that there is some form of " +
      "human force at work there, but you cannot see precisely what it is."));
    add_item(({"clearing","ground"}), BSN(
      "Not more than thirty feet in circumference, this small grassy " +
      "clearing provides for both sunlight and moisture and seems very well " +
      "nourished. Sloping gradually steeper at the base of the hill, the " +
      "ground grows thicker with trees and bushes and a path leads out of " +
      "the clearing to the northwest."));
    add_item(({"trees"}), BSN(
      "The side of the hill is covered with trees which grow thinner with " +
      "elevation. The nearest ones are a good fifteen paces away."));
    add_exit(DRUEDAIN_DIR + "amon-din/ad1","northeast", 0, 2);
    add_exit(DRUEDAIN_DIR + "amon-din/ad3","northwest", 0, 2);

    set_up_herbs( ({ HERB_DIR + "coccinea",
                     ONE_OF_LIST(HERBS), ONE_OF_LIST(HERBS), }),
                          ({ "ground","clearing", }),
                  3 );

}

string
exa_hill()
{
    string  htxt;

    htxt = "Tall and silent, the mount of Amon Din dwarfs all in the immediate " +
      "area. For many years it has stood as the closest beacon hill to the " +
      "Rammas Echor, serving as a signal for allied reinforcement in times " +
      "of great need. Only the very top of the hill is bare, and a small " +
      "building is visible upon the leveled peak.";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        htxt += " A bright flame is visible above the building. The"
              + " beacon has been lit!";
    }
    return BSN(htxt);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv( ob, from);
    if (from == find_object(AMON_DIR + "fallroom3"))
    {
        if (!living(ob))
        {
            tell_room(TO, CAP(LANG_ADDART(ob->short()))+" tumbles down"
              + " from the slope of the hilltop and comes to a rest"
              + " in the center of the clearing.\n", ob);
            return;
        }

        tell_room(TO, QCNAME(ob) + " comes tumbling down from the slope"
          + " of the hilltop and lands in a dusty heap in the center of"
          + " the clearing.\n", ob);
        return;
    }

    return;
}
