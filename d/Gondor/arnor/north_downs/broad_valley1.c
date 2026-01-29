inherit "/d/Gondor/arnor/arnor_room.c";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/arnor/north_downs/nd_defs.h"
#include "/d/Gondor/common/lib/herb_list.h"

void   reset_room();
string set_arnor_long();

object *orcs = allocate(3);

void
create_gondor()
{
    int     i;
    string *herbs;

    set_short("Western part of a broad valley in the North Downs");
    set_long("@@set_arnor_long@@");

    add_exit(NORTH_DOWNS_DIR + "ridge3",        "west",      0, 3);
    add_exit(NORTH_DOWNS_DIR + "broad_valley6", "north",     0, 2);
    add_exit(NORTH_DOWNS_DIR + "broad_valley2", "south",     0, 2);
    add_exit(NORTH_DOWNS_DIR + "broad_valley3", "southeast", 0, 2);

    herbs = ({ HERBS[random(sizeof(HERBS))],    
               HERBS[random(sizeof(HERBS))],
               HERBS[random(sizeof(HERBS))] });

    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_prop(OBJ_I_SEARCH_TIME, 8);

    set_search_places(({ "grass", "ground" }));
    for(i = 0; i < sizeof(herbs); i++)
        add_herb_file(herbs[i]);

    reset_room();
}

void
reset_room()
{
    int     i;

    for (i = 0; i < sizeof(orcs); i++)
    {
        if (!objectp(orcs[i]))
        {
/* the orcs must be armed from themselves or they will not be properly armed */
            orcs[i] = clone_object(NPC_DIR + "orcs");
            orcs[i]->move_living("leaves.\n", TO);
        }
    }

    set_searched(0);
}

string
set_arnor_long()
{
   string desc;

   desc = "In the western part of a broad valley in the North Downs. "+
   "Bushes crowd together everywhere on the valley floor. "+
   "To the west a gentle slope leads up from the valley to a hill. ";
   desc += query_arnor_time();

   return BSN(desc);
}
