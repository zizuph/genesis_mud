
/* road_start.c
 * Gamwich
 * The Road into town
 * The Start of the road, just SE of town
 * Created 23 February 1995 by Farlong@Genesis 
 */

inherit "/d/Shire/eastroad/eroad";

#include "defs.h"
#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"

string *herbs;
object hobbit;

void
reset_room()
{

    if(!hobbit)
    {
        hobbit=clone_object(ER_DIR+"npc/bighobbit");
        hobbit->arm_me();
        hobbit->move(TO);
    }
}

void
create_room()
{
    int i;

    area="just outside";
    areaname="Gamwich";
    land="the West Farthing of the Shire";
    areatype=8;
    areadesc="field";
    grass="wild";

    extraline="The road here leads into the town square of Gamwich, "+
        "just a step to the northwest.  A small sign is planted "+
        "nearby, apparently a welcome of travellers to this tiny "+
        "hobbit-village.  The path, lined by carefully-laid stones "+
        "of varying colors and sizes, continues off to the southeast, "+
        "where it eventually approaches the hamlet of Tighfield.  "+
        "On either side of the road, off to the east and southwest, "+
        "stand fields of wild grasses.";

    add_item(({"stones","stone","large stones","edge","edges",
        "road edges","roads edges","road edge","roads edge",
        "road's edges","road's edge"}),"A number of large stones are "+
        "set up along both edges of the path, nicely defining the "+
        "road's boundaries as it heads here from east to west.\n");
    add_item(({"road","path"}),"The road, lined at either side by "+
        "nicely-arranged stones, is dirt, and heads from east, toward "+
        "Tighfield, to west, toward Gamwich.\n");
    add_item(({"field","fields","open field","open fields"}),
        "Fields of wild grasses lie on either side of the "+
        "road, to the north and south.\n");
    add_item(({"grass","grasses","wild grass","wild grasses"}),
        "Long, wild grasses fill the Shire fields immediately "+
        "to the north and south of this road, just outside of the "+
        "hamlet of Gamwich.\n");
    add_item("sign","The sign welcomes travellers to Gamwich.\n");

    add_cmd_item("sign","read","The sign reads: Welcome "+
        "to Gamwich!\n");

    add_exit(GAMWICH_DIR+"square_se","northwest");
    add_exit(GAMWICH_DIR+"road_se","southeast");

    herbs=({HERBS[random(sizeof(HERBS))],
        HERBS[random(sizeof(HERBS))],
        HERBS[random(sizeof(HERBS))]});

    for(i=1; i<sizeof(herbs);i++)
        add_herb_file(herbs[i]);

    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,8);

    set_search_places(({"stones","stone","large stones","large stone",
        "road","path","edges","edge","road's edge","road's edges",
        "path's edge","path's edges","road edge","road edges",
        "path edge","path edges"}));

    make_the_room();

    reset_room();
}

