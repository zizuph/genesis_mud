#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
    set_area ("bend on");
    set_areaname ("the Great East Road");
    set_land ("Rhudaur");
    set_areatype (AREATYPE_ROAD);
    set_areadesc ("shadow laden");
    set_grass ("sparse, sickly");
    set_treetype ("pine");

    set_extraline ("The Hoarwell river rushes along its course under " +
    "the Last Bridge to the northwest, while relative silence casts its spell " +
    "from all the other directions.  The tree covered hills of the Trollshaws " +
    "dominate the view in all directions, except to the east and northwest " +
    "where the road winds its muddy way.  " +
    "The road continues to the northwest and east from here.");

add_item (({"great east road", "road", "muddy road", "mud"}),
"The Great East Road, an ancient road for travellers, is completely " +
"under mud due to the recent rains.  Thus, it offers no obvious signs " +
"of other travellers. \n");
add_item (({"hoarwell", "river", "hoarwell river", "last bridge", "bridge"}),
"The sounds of the Hoarwell's water rushing under Last Bridge can faintly " +
"be heard from a distance.  It is too far away to be seen clearly enough " +
"for details through the shadows cast upon the road by the hills and " +
"trees of Rhudaur.\n");
add_item (({"shadow", "shadows"}),
"Deep shadows surrounding the area aid creatures that choose to " +
"hide in the darker regions.\n");
add_item (({"tree", "trees", "pine trees", "pines"}),
"Tall pine trees blanket the hills of the Trollshaws.  Growing close " +
"together, they help hold Rhudaur's secrets from casual observers " +
"in both the northern and southern directions.\n");
add_item (({"south", "southern trees", "southern pine trees"}),
"Widely spaced pine trees on the southern side of the road battle with " +
"patches of grass, thickets, and heather.  The result is of fleeting " +
"glimspes of the river valley holding the Hoarwell on its way south.\n");
add_item (({"grass", "thicket", "thickets", "heather"}),
"In a battle for light, patches of grass, thickets, and heather fight for " +
"what light passes through the tops of pine trees.\n");

/* add a VBFC for the northern trees so they may be searched to find
*the path leading north deeper into the back country of the Trollshaws. */

    add_exit (ER_DIR + "erb39", "northwest", 0, 1);
    add_exit (ER_DIR + "erb41", "east", 0, 1);

}
