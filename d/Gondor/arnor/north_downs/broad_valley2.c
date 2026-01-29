inherit "/d/Gondor/arnor/arnor_room.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/arnor/north_downs/nd_defs.h"
#include "/d/Gondor/common/lib/herb_list.h"

void   reset_room();
string set_arnor_long();

void
create_gondor()
{
    int     i;
    string *herbs;

    set_short("Southwestern part of a broad valley in the North Downs");
    set_long("@@set_arnor_long@@");

    add_exit(NORTH_DOWNS_DIR + "broad_valley1", "north", 0, 3);
    add_exit(NORTH_DOWNS_DIR + "broad_valley3", "east", 0, 3);

    herbs = ({ HERBS[random(sizeof(HERBS))],    
               HERBS[random(sizeof(HERBS))],
               HERBS[random(sizeof(HERBS))] });

    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_prop(OBJ_I_SEARCH_TIME, 8);

    set_search_places(({ "grass", "ground" }));
    for(i = 0; i < sizeof(herbs); i++)
        add_herb_file(herbs[i]);
}

void
reset_room()
{
    set_searched(0);
}

string
set_arnor_long()
{
   string desc;

   desc = "In the southwestern part of a broad valley in the North Downs. "+
   "This part is a bit higher up in the valley, just above the bushes. "+
   "South the valley ends in a steep slope. "+
   "Small hollows filled with heather dot the slope. "+
   "In the distance to the west a ridge fades away. ";
   desc += query_arnor_time();

   return BSN(desc);
}
