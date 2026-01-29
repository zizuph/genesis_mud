inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
#include "/d/Gondor/common/lib/herb_list.h"

void reset_room();

void create_helmsdeep_room()
{
    int     i;
    string *herbs;

    set_short_desc("A grassy slope");
    set_extra_long("A grassy slope that rises slightly to the south. The grass "+
    "is lush and green, and cliffs rise high above "+
    "the gorge. Further up the the slope is the Deeping-wall. ");

    H_WALL;
    GRASS;
    CLIFFS;
    GORGE;
    MOUNTAINS;
    add_item("slope", "A field of grass slopes up to Helm's wall.\n");

    add_exit(ROH_DIR+"horn/gorge/croad","north",0);
    add_exit(ROH_DIR+"horn/gorge/ofield2","south",0,3);

    herbs = ({ HERBS[random(sizeof(HERBS))],
               HERBS[random(sizeof(HERBS))],
               HERBS[random(sizeof(HERBS))] });
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,8);

    set_search_places(({"grass", "ground", "slope"}));
    for(i = 0; i < sizeof(herbs); i++)
        add_herb_file(herbs[i]);
}

void
reset_room()
{
    set_searched(0);
}
