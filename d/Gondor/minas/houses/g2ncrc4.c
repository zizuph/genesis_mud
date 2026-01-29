inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"

#define CLIMB_SKILL	20

void
create_room()
{
    set_short("In a private garden in Fourth Circle of Minas Tirith");
    set_long(BSN("This is a private garden in the Fourth Circle of Minas "
      + "Tirith. It lies between large houses to the west and the south "
      + "and the Fourth Wall of the city to the east. A sandy path is "
      + "winding through beds planted with flowers and herbs and around "
      + "a big tree in the center of this part of the garden."));

    add_item(({"flowers", "white flowers", "yellow flowers", }), BSN(
        "The white and yellow flowers make the garden smell pleasant. They "
      + "are placed in well tended flowerbeds."));
    add_item(({"path","sandy path", }),BSN(
        "The path is well tended and has been raked recently. It is enclosed "
      + "on both sides by a row of small stones. The complete lack of weeds "
      + "on the path and between the stones tells a lot about the gardener "
      + "that is working here."));
    add_item(({"flower-beds","flowerbeds"}), BSN(
        "The flowerbeds are well tended, and white and yellow flowers "
      + "fill the garden with a pleasant smell. Other beds have been planted "
      + "with many different herbs."));
    add_item(({"tree", "big tree", }), BSN(
        "There is only a single tree in the garden, a big rowan tree right "
      + "in the middle of this southern part of the garden."));
    add_item(({ "houses", "house" }), BSN("These houses look rather large and "
      + "well constructed. This must be a district where the more "
      + "well-off people of Minas Tirith live."));
    add_item(({"wall", "fourth wall", }), BSN(
        "The Fourth Wall of the city borders the garden on the east. It "
      + "rises many yards into the sky, made from huge boulders hewn "
      + "from the same white rock onto which the city has built."));

    add_exit(MINAS_DIR+"houses/h3ncrc4","west",0,1);
    add_exit(MINAS_DIR+"houses/g3ncrc4","north",0,1);

    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,3);
    set_search_places(({"flowers","flower-beds","flowerbeds","garden"}));

    add_herb_file(ONE_OF_LIST(HERBS));
    add_herb_file(ONE_OF_LIST(HERBS));
    add_herb_file(ONE_OF_LIST(HERBS));
}

int
do_climb(string str)
{
    int     s_climb;
    object  tp = TP;
    string  vb = query_verb();

    if (!strlen(str) || (member_array(str,
        ({"tree", "big tree", "rowan", "rowan tree", "big rowan tree", }))
        == -1))
    {
        NFN(CAP(vb) + " what?");
        return 0;
    }

    s_climb = tp->query_skill(SS_CLIMB) / 2;
    s_climb += random(2*s_climb);

    if (s_climb > CLIMB_SKILL)
    {
        set_dircmd(str);
        write("You climb up into the big rowan tree.\n");
        tp->move_living("up into the tree", MINAS_DIR + "houses/g4ncrc4");
    }
    else
    {
        write("You try to climb up into the big rowan tree, but you fail.\n");
        say(QCTNAME(tp) + " tries to climb the big rowan tree, but fails.\n");
    }
    return 1;
    
}

void
init()
{
    ::init();

    add_action(do_climb, "climb");
}

