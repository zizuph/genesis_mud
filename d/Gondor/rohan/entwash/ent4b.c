/*
 *  /d/Gondor/rohan/entwash/ent4b.c
 *
 *  An interesting little room.
 *
 *  Coded by Gorboth, Sept 1995
 *
 *  Special thanks to: Jeremiah
 */
inherit "/d/Gondor/rohan/entwash/entwash";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define LOG_RING		"/d/Gondor/log/ent_ring"
#define MIN_AWARENESS		25

int   found,
      c;

string exa_roots();

void
create_swamp()
{
    set_extra_long("A swift stream flows by to the south, making its"
      + " way east to meet with the Anduin. Some very tall reeds are"
      + " growing along the bank. Across the stream, a ways to the"
      + " south, the plains of Anorien are visible through the fog.");

    add_item(({"stream","swift stream"}), BSN("This stream retains"
      + " a large amount of the current from the fractured Entwash."
      + " It runs to the east, where it disappears into the mist."
      + " Looking across the stream to the south, the grasslands of"
      + " Anorien can be seen extending for miles."));
    add_item(({"grasslands","grassland","plains","plain",
      "plains of anorien","grasslands of anorien"}), BSN(
        "Through the mist to the south, the plains of Anorien are"
      + " visible trailing into the distance for miles."));
    add_item(({"bank","banks"}), BSN("This swift stream has carved a"
      + " slight bank into the mud here. A particularly large patch"
      + " of reeds is growing alongside of the water."));
    add_item(({"reed","reeds","patch","patch of reeds"}), BSN(
        "A tall group of reeds is growing alongside of the stream here."
      + " Water flows in and out from among the stems, and every so"
      + " often, a leaf or some other form of debris will drift by and"
      + " nudge one of the tall shafts."));
    add_item(({"shaft","shafts","stem","stems"}), BSN(
        "Most of these stems shoot straight out of the surface of the"
      + " water, beneath which a thick system of roots is meshed."));
    add_item(({"root","roots"}), "@@exa_roots");

    add_exit(ENTWASH_DIR + "ent4a", "north");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();
}

void
reset_room()
{
    found = 0;
    c = 1;
}

varargs int
set_up_herbs()
{
    return 0;
}

string
do_search(object pl, string str)
{
    int as;
    object  ob;

    if (!strlen(str) || (member_array(str, ({"root", "roots"})) == -1))
        return herb_search(pl, str);

    if ((((as = pl->query_skill(SS_AWARENESS)) < MIN_AWARENESS) &&
        random((100 - as + MIN_AWARENESS)/MIN_AWARENESS*2)) || (c == 0))
        return BSN("You search through the tangled mass of roots, but"
          + " cannot seem to find anything. Perhaps there is nothing"
          + " there but mud.");

    ob = clone_object(ENTWASH_DIR + "obj/ent_ring");
    if (ob->move(TP))
    ob->move(TP, 1);
    c--;
    found = 1;            //  to change root desc
    write_file(LOG_RING, TP->query_name() + " ("
      + TP->query_average_stat() +") found the Entwash Ring, "
      + ctime(time()) + ".\n");
    return("You search through the tangled roots and find " +LANG_ASHORT(ob)+".\n");
}

string
exa_roots()
{
    string  desc;

    if (found == 0)
    {
        desc = "There seems to be something lodged in these roots,"
          + " but you don't seem to be able to get a good look at it.";
    }
    else
    {
        desc = "These roots are tangled badly. It looks as if some"
          + "thing or someone has dug through them recently.";
    }

    return BSN(desc);
}
