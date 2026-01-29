inherit "/d/Gondor/rohan/entwash/entwash";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define  MIN_AWARENESS			15


int     grubb,		// has grubb been found? 1:yes 0:no
        c;

void
create_swamp()
{
    set_extra_long("This is a rather sad and lonely area of the fens."
      + " The occasional cry of a raven is the only thing that seems"
      + " break the gloom which hangs over the Entwash.");

    add_item(({"hole","holes","root","roots"}),
        "@@exa_holes");
    add_item(({"raven","ravens"}), BSN("The raven is not visible here,"
      + " but perhaps a nest has been built in the nearby tree."));

    if (!objectp(present("entwash_live_tree")))
    {
         clone_object(ENTWASH_DIR + "obj/live_tree")->move(TO);
    }

    add_exit(ENTWASH_DIR + "ent3h", "north");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();
}

void
reset_room()
{
    c = 1;
    grubb = 0;
}

string
exa_holes()
{
    string  txt;

    switch(grubb)
    {
        case 0:
            txt = "Small holes are visible among the roots"
              + " at the base of this tree. They are roughly"
              + " the width of a human finger in diameter."
              + " Whatever bored them is probably embedded"
              + " within the trunk.";
            break;
        case 1:
            txt = "Someone seems to have dug out a portion"
              + " of the bark at the base of this tree amongst"
              + " a number of small finger-width holes.";
            break;
    }
    return BSN(txt);
}

string
do_search(object pl, string str)
{
    int as;
    object obj;

    if (!strlen(str) || (member_array(str,
      ({"alder","oak","willow","tree","root","roots","hole","holes","trunk"})) == -1))
        return herb_search(pl, str);

    if ((((as = pl->query_skill(SS_AWARENESS)) < MIN_AWARENESS) &&
        random((100 - as + MIN_AWARENESS)/MIN_AWARENESS*2)) ||
        (c == 0))
        return BSN("You dig around in the bark at the base of the"
          + " tree, but it seems someone has already found whatever"
          + " may have been there.");

    obj = clone_object(ENTWASH_DIR + "obj/ent_grubb");
    if (obj->move(TP))
    obj->move(TP, 1);
    c--;
    grubb = 1;           // The grubb is found!
    return BSN("You dig in the bark around the holes at the base of"
      + " the tree, and find a slimy black grubb!");
}

varargs int
set_up_herbs()
{
    return 0;
}
