inherit "/d/Gondor/common/lib/area_room.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

object *rabbit = allocate(2 + random(3));

public void
create_area_room()
{
    set_areatype(7);
    set_areadesc("fern-covered slope");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("bay and cedar");
    set_extraline("The thick fernbed is surrounded by a thicket of "
      + "dark-leaved bay trees and steep banks rising to the south and the "
      + "east. High on the banks, old cedars are towering. Among the high "
      + "ferns and in the shadow of the bank and the thicket, you are hidden "
      + "from casual glances. There is no way to leave again but to the "
      + "southwest. Sweet odours from herbs and flowers are in the air "
      + "everywhere.");
    add_item(({"mountains","mountain-range","mountain","ephel duath"}), 
        "From here the mountains are hidden by trees and the stony ridge to "
      + "the east.");
    add_item(({"bank","bay trees","cedar","groves","thickets","thicket",
        "grove"}), BSN(
        "Dark-leaved bay trees form a thicket all around you. To the south "
      + "and the east the thicket is climbing the steep banks, rising to old "
      + "cedars towering high above. Only to the southwest the fernbed "
      + "continues."));
    add_item(({"flower","flowers","herbs","forest","wood","woods","fern",
        "fern bed"}), BSN(
        "The fern forms a deep brown bed here. It grows high enough to hide "
      + "someone lying down from casual glances. Among the ferns, herbs and "
      + "flowers are growing. You can recognize mints and lilies by the "
      + "smell, and parsleys are sprouting under the trees."));
    add_item(({"lake","basin","pool","water"}), BSN(
        "The small lake lies in the broken ruins of an ancient stone basin. A "
      + "small stream is feeding it, and at the far end the water spills out "
      + "again over a stony lip."));

    add_prop(ROOM_I_HIDE,1);

    set_up_herbs( ({ HERB_DIR+"garlic", HERB_DIR+"caraway", HERB_DIR+"savory",
                     HERB_DIR+"laurel", HERB_DIR+"redweed", HERB_DIR+"foxglove",
                     HERB_DIR+"curugwath", }),
                 ({ "forest","ground","slope","forest"}), 3);

    add_exit(ITH_DIR + "nforest/slope", "southwest", 0, 1);

    reset_room();
}

public void
clone_rabbit()
{
    int i, s;

    for (i = 0, s = sizeof(rabbit); i < s; i++)
        if (!objectp(rabbit[i]))
        {
            rabbit[i] = clone_object(NPC_DIR + "rabbit");
            rabbit[i]->set_restrain_path(ITH_DIR + "nforest/");
            rabbit[i]->set_m_in("hops into view");
            rabbit[i]->move_living("down", TO);
            set_alarm(30.0 + rnd() * 60.0, 0.0, clone_rabbit);
            return;
        }
}

public void
reset_room()
{
    int n;

    set_searched(-2);

    set_alarm(20.0 + rnd() * 40.0, 0.0, clone_rabbit);
}
