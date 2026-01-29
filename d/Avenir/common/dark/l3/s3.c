inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"
create_room()   {

        set_short("Fork in the dark tunnel");
        set_long(
"The tunnel branches here, with what seems to be a cavern to the "
+"northwest. The walls sparkle with a dazzling light from the "
+"moisture that trickles down them, and what was once dust at your "
+"feet has turned to thick mud with the water that trickles down "
+"from the walls. The air has a strong smell of mold and must to it.\n");

        AI(({"wall","walls"}),"The walls, constructed ages ago, are "
+"of a smooth stone that does not seem to be indiginous to the caverns. "
+"It is a white rock with swirling, light blue patterns running through "
+"it. The walls have been worn with the passage of time, and cracks have "
+"appeared in the once perfectly smooth surface, from where a small "
+"amount of water is seeping in. The water runs down the walls to "
+"the floor, making them glisten and sparkle with a dazzling light.\n");

        AI(({"crack","cracks"}),"The beautiful white walls are covered "
+"with tiny webs of cracks all through them, possibly due to some "
+"movement of the land ages ago. From the cracks you can discern a "
+"small trickle of water running in.\n");

        AI(({"dust","mud"}),"The layer of dust that lies throughout "
+"these tunnels had been turned to a thick, sticky mud, making a "
+"stark contrast to the beautiful walls of this passage.\n");

        AI(({"dark","darkness"}),"The darkness seems to have a life "
+"of its own, stretching itself out in an attempt to engulf you "
+"within.\n");

        AI(("floor"),"The floor is smooth, and is carved out of the "
+"living rock itself, unlike the walls. The floor is covered in a "
+"morass of thick, grey mud.\n");

        AI(("water"),"Where this water comes from is a mystery, and "
+"will probably always remain so. It gently seeps from the cracks in "
+"the walls, making them glisten and shine.\n");

        AI(({"cave","cavern"}),"The cavern to the northwest seem to "
+"be small and naturally formed, as opposed to the artificially "
+"constructed passage you are in now. A strange smell comes from the "
+"cave, making you hesitant to enter it.\n");

        add_exit("/d/Avenir/common/dark/l3/s4","south",0);
        add_exit("/d/Avenir/common/dark/l3/s2","north",0);
        add_exit("/d/Avenir/common/dark/l3/sc1","northwest",0);

        add_prop(ROOM_I_LIGHT,0);
        add_prop(ROOM_I_INSIDE,1);

}

