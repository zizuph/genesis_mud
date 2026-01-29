
/* road_far_se.c
 * Gamwich
 * The Road into town
 * Far southeastern end
 * Created 19 February 1995 by Farlong@Genesis 
 */

inherit "/d/Shire/eastroad/eroad";

#include "defs.h"
#include "/d/Shire/common/herbs/herb_list.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"

string *herbs;

void
create_room()
{
    int i;

    area="near";
    areaname="Gamwich";
    land="the West Farthing of the Shire";
    areatype=8;
    areadesc="field";
    grass="wild";

    extraline="A wide and well-kept dirt path heads "+
        "westward here, curving up into the small hobbit village "+
        "of Gamwich, and to the east, out towards the hamlet of "+
        "Tighfield.  Large stones, neatly aligned, line the "+
        "road's edges; just beyond stand open fields of wild "+
        "grasses.";

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

    add_exit(GAMWICH_DIR+"road_turn","west");

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
}

