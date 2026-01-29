inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/rohan/horn/hd_defs.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
#include "/d/Gondor/common/lib/herb_list.h"

void reset_room();

void create_helmsdeep_room()
{
    int     i;
    string *herbs;

    set_short_desc("A grassy field");
    set_extra_long("A grassy field below the Rock. The grass is "+
    "lush and green, and cliffs rise high above "+
    "either side of the gorge. Further "+
    "to the north is the Dike, the field continues west, "+
    "and to the southeast is the causeway. ");

    set_track_dir1("west");
    set_track_dir2("southeast");

    add_item(({"keep","hornburg"}),BS("To the south, the "+
    "Rock spur rises steeply. High on the ridge, there's a wall, "+
    "and behind that a tower.\n"));
    add_item(({"rock","Rock"}),"Upon the Rock the keep is built.\n");
    add_item("causeway", "You can't see any details from here.\n");
    add_item(({ "ground", "track", "tracks", "footprints" }),
    	find_tracks);
    FIELD;
    GRASS;
    CLIFFS;
    GORGE;
    DIKE;
    MOUNTAINS;

    add_exit(ROH_DIR+"horn/gorge/ofield5","west",0);
    add_exit(ROH_DIR+"horn/gorge/causeway","southeast",0);

    herbs = ({ HERBS[random(sizeof(HERBS))],
               HERBS[random(sizeof(HERBS))],
               HERBS[random(sizeof(HERBS))] });
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,8);

    set_search_places(({"gorge", "grass", "ground", "slope"}));
    for(i = 0; i < sizeof(herbs); i++)
        add_herb_file(herbs[i]);
}

void
reset_room()
{
    set_searched(0);
}
